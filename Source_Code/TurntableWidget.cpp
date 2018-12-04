#include "TurntableWidget.h"

TurntableWidget::TurntableWidget(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(1000);

    QPalette background_palette;
    backgroud_color=QColor(179, 179, 179);
    background_palette.setColor(QPalette::Background,backgroud_color);
    setPalette(background_palette);
    setAutoFillBackground(true);


    hideButton=new QPushButton(this);
    hideButton->setGeometry(950,20,30,30);
    hideButton->setStyleSheet("QPushButton{border:0px;border-image:url(:/images/Turntable/hide.png)}\
                                                 QPushButton:hover{background:rgb(100,100,100)}");

    record_timer=new QTimer(this);
    record_timer->setInterval(25);
    connect(record_timer,&QTimer::timeout,this,&TurntableWidget::update_record);

    stylus_in_timer=new QTimer(this);
    stylus_in_timer->setInterval(15);
    connect(stylus_in_timer,&QTimer::timeout,this,&TurntableWidget::update_stylus_in);

    music_titelLabel=new QLabel(this);
    music_erLabel=new QLabel(this);
    special_Label=new QLabel(this);
    QPalette text_palette;
    text_palette.setColor(QPalette::WindowText,QColor(255,250,200));
    QFont font_title("微软雅黑",20);
    QFont font_normal("微软雅黑",12);
    music_titelLabel->setFont(font_title);
    music_titelLabel->setPalette(text_palette);
    music_erLabel->setFont(font_normal);
    music_erLabel->setPalette(text_palette);
    special_Label->setFont(font_normal);
    special_Label->setPalette(text_palette);
    music_titelLabel->setText("网易云音乐");
    music_titelLabel->setGeometry(610,75,200,35);
    music_erLabel->setText("歌手");
    music_erLabel->setGeometry(560,130,80,25);
    special_Label->setText("来源");
    special_Label->setGeometry(760,130,140,25);

}

void TurntableWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);


    //first draw; for that: record cover this pix
    if(pix_cd.isNull())
        pix_cd.load(":/images/Turntable/cdCover.png");
    painter.save();
    painter.translate(85,110);
    painter.translate(195,195);
    painter.rotate(record_angle);
    painter.translate(-75,-75);
    painter.drawPixmap(0,0,150,150,pix_cd);
    painter.restore();

    QPixmap pix_record;
    pix_record.load(":/images/Turntable/record.png");
    painter.save();
    painter.translate(85,110);//move to rect left_top
    painter.translate(195,195);
    painter.rotate(record_angle);
    painter.translate(-195,-195);
    painter.drawPixmap(0,0,390,390,pix_record);
    painter.restore();

    QPixmap pix_stylus;
    pix_stylus.load(":/images/Turntable/stylus.png");
    painter.save();
    painter.translate(30,-200);
    painter.translate(250,250);
    painter.rotate(stylus_angle);
    painter.translate(-250,-250);
    painter.drawPixmap(0,0,500,500,pix_stylus);
    painter.restore();
}

void TurntableWidget::update_record()
{
    record_angle += 1;
    if(record_angle > 360)
    {
        record_angle = 0;
    }
    update();
}
void TurntableWidget::update_stylus_in()
{
    stylus_angle += 1;
    if(stylus_angle > 30)
    {
        stylus_in_timer->stop();
    }
    update();
}
void TurntableWidget::update_stylus_out()
{
    stylus_angle = 0;
    update();
}














