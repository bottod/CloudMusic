#include "AnimationWidget.h"

AnimationWidget::AnimationWidget(QWidget *parent)
    : QFrame(parent)
{
    for(int i=1;i<image_count+1;i++)
    {
        QPixmap temp_label = QPixmap(":/images/"+QString::number(i)+".png");
        label_group.push_back(temp_label);
    }

    int width = this->width();
    int height = this->height();

    int pos_center_xstart =(width-center_width)/2;
    int pos_center_ystart=(height-center_hieght)/2;
    center_rect.setRect(pos_center_xstart,pos_center_ystart,center_width,center_hieght);
    center_label = new QLabel(this);
    center_label->setPixmap(label_group[0]);
    center_label->setGeometry(pos_center_xstart,pos_center_ystart,center_width,center_hieght);

    int pos_left_xstart = pos_center_xstart - margin_width;
    int pos_left_ystart = pos_center_ystart + center_hieght - margin_height;
    left_rect.setRect(pos_left_xstart,pos_left_ystart,margin_width,margin_height);
    left_label =new QLabel(this);
    left_label->setPixmap(label_group[5]);
    left_label->setGeometry(pos_left_xstart,pos_left_ystart,margin_width,margin_height);

    int pos_right_xstart = pos_center_xstart + center_width;
    int pos_right_ystart = pos_center_ystart + center_hieght - margin_height;
    right_rect.setRect(pos_right_xstart,pos_right_ystart,margin_width,margin_height);
    right_label =new QLabel(this);
    right_label->setPixmap(label_group[1]);
    right_label->setGeometry(pos_right_xstart,pos_right_ystart,margin_width,margin_height);

    //line bar
    transferBar = new QToolBar(this);
    transferBar->setGeometry(pos_center_xstart+center_width/2-40,pos_center_ystart+center_hieght+10,17*image_count*2,24);
    transferBar->setStyleSheet("QToolButton{border:0px}");
    transferBar->setIconSize(QSize(17,23));
    for(int actions_num = 0;actions_num < image_count;actions_num++)
    {
        lineAction[actions_num]=new QAction(QIcon(":/images/line.png"),"",transferBar);
        lineAction[actions_num]->setData(actions_num);
        connect(lineAction[actions_num],&QAction::hovered,this,&AnimationWidget::onHoverAction);
        transferBar->addAction(lineAction[actions_num]);
    }
    lineAction[default_choose]->setIcon(QIcon(":/images/lineChose.png"));

    moveAnimation_left = new QPropertyAnimation(left_label,"geometry");
    moveAnimation = new QPropertyAnimation(center_label,"geometry");
    moveAnimation_right=new QPropertyAnimation(right_label,"geometry");

}

AnimationWidget::~AnimationWidget()
{

}

// a small bug; rect mess
void AnimationWidget::resizeEvent(QResizeEvent* event)
{

    int width = this->width();
    int height = this->height();

    int changesize = event->size().width() - event->oldSize().width();

    margin_width = margin_width + static_cast<int>(changesize * 0.15);
    if(margin_width > 542)
        margin_width = 532;
    else if(margin_width < 110)
        margin_width = 100;

    int pos_center_xstart =(width-center_width)/2;
    int pos_center_ystart=(height-center_hieght)/2;
    center_rect.setRect(pos_center_xstart,pos_center_ystart,center_width,center_hieght);
    center_label->setGeometry(pos_center_xstart,pos_center_ystart,center_width,center_hieght);

    transferBar->setGeometry(pos_center_xstart+center_width/2-40,pos_center_ystart+center_hieght+10,17*image_count*2,24);

    int pos_left_xstart = pos_center_xstart - margin_width;
    int pos_left_ystart = pos_center_ystart + center_hieght - margin_height;
    left_rect.setRect(pos_left_xstart,pos_left_ystart,margin_width,margin_height);
    left_label->setGeometry(pos_left_xstart,pos_left_ystart,margin_width,margin_height);

    int pos_right_xstart = pos_center_xstart + center_width;
    int pos_right_ystart = pos_center_ystart + center_hieght - margin_height;
    right_rect.setRect(pos_right_xstart,pos_right_ystart,margin_width,margin_height);
    right_label->setGeometry(pos_right_xstart,pos_right_ystart,margin_width,margin_height);

    center_label->raise();

}

void AnimationWidget::onHoverAction()
{
    int hover_action_num = 0;
    QAction *actionSender = reinterpret_cast<QAction *>(sender());
    for(int action_num = 0; action_num < image_count; action_num++)
    {
        if(lineAction[action_num] != actionSender)
            lineAction[action_num]->setIcon(QIcon(":/images/line.png"));
        else
            hover_action_num = action_num;
    }
    actionSender->setIcon(QIcon(":/images/lineChose.png"));
    transferBar->setCursor(QCursor(Qt::PointingHandCursor));

    if(hover_action_num > default_choose)
    {
        moveLeft();
        default_choose = hover_action_num;
        center_label->setPixmap(label_group[hover_action_num == 0 ? 5 : hover_action_num - 1]);
        right_label->setPixmap(label_group[hover_action_num]);
        left_label->setPixmap(label_group[hover_action_num == 5 ? 0 : hover_action_num + 1]);
    }
    else if(hover_action_num < default_choose)
    {
        moveRight();
        default_choose = hover_action_num;
        right_label->setPixmap(label_group[hover_action_num == 0 ? 5 : hover_action_num - 1]);
        left_label->setPixmap(label_group[hover_action_num]);
        center_label->setPixmap(label_group[hover_action_num == 5 ? 0 : hover_action_num + 1]);
    }

}

void AnimationWidget::moveRight()
{
    moveAnimation_left->setDuration(200);
    moveAnimation_left->setStartValue(left_rect);
    moveAnimation_left->setEndValue(center_rect);
    moveAnimation_left->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_left->start();

    moveAnimation->setDuration(200);
    moveAnimation->setStartValue(center_rect);
    moveAnimation->setEndValue(right_rect);
    moveAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation->start();

    moveAnimation_right->setDuration(200);
    moveAnimation_right->setStartValue(right_rect);
    moveAnimation_right->setEndValue(left_rect);
    moveAnimation_right->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_right->start();

}

void AnimationWidget::moveLeft()
{
    moveAnimation_left->setDuration(200);
    moveAnimation_left->setStartValue(left_rect);
    moveAnimation_left->setEndValue(right_rect);
    moveAnimation_left->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_left->start();

    moveAnimation->setDuration(200);
    moveAnimation->setStartValue(center_rect);
    moveAnimation->setEndValue(left_rect);
    moveAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation->start();

    moveAnimation_right->setDuration(200);
    moveAnimation_right->setStartValue(right_rect);
    moveAnimation_right->setEndValue(center_rect);
    moveAnimation_right->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_right->start();

}

