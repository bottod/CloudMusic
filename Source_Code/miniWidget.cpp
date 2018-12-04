#include "miniWidget.h"

miniWidget::miniWidget(QWidget *parent) : QFrame(parent)
{
    setFixedSize(250,42);

    m_mouseState = false;
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);

    setMouseTracking(true);
    init_miniWidget();
}

void miniWidget::mousePressEvent(QMouseEvent *event)
{
    m_WindowPos = this->pos();
    if(QRect(0,0,width(),height()).contains(event->pos()) && event->button() == Qt::LeftButton)
    {
        m_MousePos = event->globalPos();
        m_mouseState = true;
    }
}

void miniWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mouseState)
    {
        move(m_WindowPos + (event->globalPos() - m_MousePos));
    }
}

void miniWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mouseState = false;
}

void miniWidget::enterEvent(QEvent *)
{
    m_songNameLab->setVisible(false);
    m_singleLab->setVisible(false);
    m_palyFrame->setVisible(true);
}

void miniWidget::leaveEvent(QEvent *)
{
    m_songNameLab->setVisible(true);
    m_singleLab->setVisible(true);
    m_palyFrame->setVisible(false);
}

void miniWidget::init_miniWidget()
{
    setStyleSheet(::miniMainColor);

    m_vMainLayout = new QVBoxLayout(this);

    m_mainFrame = new QFrame;
    m_mainFrame->setFixedSize(250,42);

    m_hMainLayout = new QHBoxLayout(m_mainFrame);

    /*******************************************/
    m_photoLabel = new QLabel;
    m_photoLabel->setFixedSize(42,42);
    m_photoLabel->setCursor(Qt::PointingHandCursor);
    m_photoLabel->setStyleSheet("QLabel{border-image:url(:/images/mini/photo.png);}");

    /************************************/
    m_vInfoLayout = new QVBoxLayout;

    m_songNameLab = new QLabel;
    m_songNameLab->setFixedSize(120,18);
    m_songNameLab->setText("未知");
    m_songNameLab->setAlignment(Qt::AlignCenter);
    m_songNameLab->setStyleSheet("QLabel{color:#FFFFFF;}");

    m_singleLab = new QLabel;
    m_singleLab->setFixedSize(120,18);
    m_singleLab->setText("未知");
    m_singleLab->setAlignment(Qt::AlignCenter);
    m_singleLab->setStyleSheet("QLabel{color:#000000;}");

    m_vInfoLayout->setMargin(3);
    m_vInfoLayout->setSpacing(3);
    m_vInfoLayout->addWidget(m_songNameLab);
    m_vInfoLayout->addWidget(m_singleLab);

    /******************************************/
    m_palyFrame = new QFrame;
    m_palyFrame->setVisible(false);

    m_hPlayLayout = new QHBoxLayout(m_palyFrame);

    m_preBtn = new QPushButton;
    m_preBtn->setFixedSize(26,26);
    m_preBtn->setCursor(Qt::PointingHandCursor);
    m_preBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/last.png);}");

    m_playStateBtn = new QPushButton;
    m_playStateBtn->setFixedSize(30,30);
    m_playStateBtn->setCursor(Qt::PointingHandCursor);
    m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/play.png);}");

    m_nextBtn = new QPushButton;
    m_nextBtn->setFixedSize(26,26);
    m_nextBtn->setCursor(Qt::PointingHandCursor);
    m_nextBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/next.png);}");

    m_hPlayLayout->setMargin(0);
    m_hPlayLayout->setSpacing(9);
    m_hPlayLayout->addWidget(m_preBtn);
    m_hPlayLayout->addWidget(m_playStateBtn);
    m_hPlayLayout->addWidget(m_nextBtn);
    /****************************************************/

    m_loveBtn = new QPushButton;
    m_loveBtn->setFixedSize(15,13);
    m_loveBtn->setCursor(Qt::PointingHandCursor);
    m_loveBtn->setStyleSheet("QPushButton{background:transparent;\
                             border-image:url(:/images/mini/love.png);}");

    m_volBtn = new QPushButton;
    m_volBtn->setFixedSize(15,13);
    m_volBtn->setCursor(Qt::PointingHandCursor);
    m_volBtn->setStyleSheet("QPushButton{background:transparent;\
                            border-image:url(:/images/mini/vol.png);}");

    m_listBtn = new QPushButton;
    m_listBtn->setFixedSize(13,11);
    m_listBtn->setCursor(Qt::PointingHandCursor);
    m_listBtn->setStyleSheet("QPushButton{background:transparent;\
                             border-image:url(:/images/mini/list.png);}");

    /***************************************/
    m_vSysLayout = new QVBoxLayout;

    m_closeBtn = new QPushButton;
    m_closeBtn->setFixedSize(8,7);
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setStyleSheet("QPushButton{background:transparent;\
                              border-image:url(:/images/mini/close.png);}");
    connect(m_closeBtn,&QPushButton::clicked,this,&miniWidget::hide);
    //just hide not close

    m_recoveryWinBtn = new QPushButton;
    m_recoveryWinBtn->setFixedSize(8,6);
    m_recoveryWinBtn->setCursor(Qt::PointingHandCursor);
    m_recoveryWinBtn->setStyleSheet("QPushButton{background:transparent;\
                                    border-image:url(:/images/mini/winMode.png);}");

    m_vSysLayout->setSpacing(6);
    m_vSysLayout->setMargin(6);
    m_vSysLayout->addWidget(m_closeBtn);
    m_vSysLayout->addWidget(m_recoveryWinBtn);
    m_vSysLayout->addStretch();
    /********************************************/

    m_hMainLayout->setMargin(0);
    m_hMainLayout->addWidget(m_photoLabel);
    m_hMainLayout->addLayout(m_vInfoLayout);
    m_hMainLayout->addStretch();
    m_hMainLayout->addWidget(m_palyFrame);
    m_hMainLayout->addStretch();
    m_hMainLayout->addWidget(m_loveBtn);
    m_hMainLayout->addWidget(m_volBtn);
    m_hMainLayout->addWidget(m_listBtn);
    m_hMainLayout->addLayout(m_vSysLayout);


    m_vMainLayout->setMargin(0);
    m_vMainLayout->addWidget(m_mainFrame);
}
