#include "SongListFrame.h"

SongListFrame::SongListFrame(QWidget *parent) : QFrame(parent)
{
    setFixedSize(580,470);
    setStyleSheet("QFrame{border-color:#E1E1E2;border-width: 0.5px 0 0 0.5px;border-style: solid;}");

    initFrame();
    initPlayList();
    initConnect();
}

void SongListFrame::focusOutEvent(QFocusEvent *)
{
    this->hide();
}

void SongListFrame::initFrame()
{
    m_BtnFrame = new QFrame;
    m_BtnFrame->setFixedHeight(41);
    m_BtnFrame->setStyleSheet("QFrame{background:#f0f0f0}");

    m_PlayingBtn = new QPushButton("播放列表",m_BtnFrame);
    m_PlayingBtn->setGeometry(185,8,105,25);
    m_PlayingBtn->setCursor(Qt::PointingHandCursor);
    m_PlayingBtn->setCheckable(true);
    m_PlayingBtn->setChecked(true);
    m_PlayingBtn->setStyleSheet("QPushButton{background:#ffffff;color:#7c7085;border:node;border-top-left-radius:5;border-bottom-left-radius:5}\
                                 QPushButton:hover{background:#f5f5f7}\
                                 QPushButton:checked{background:#7c7085;color:#ffffff}");

    m_PlaysBtn = new QPushButton("历史记录",m_BtnFrame);
    m_PlaysBtn->setGeometry(290,8,105,25);
    m_PlaysBtn->setCursor(Qt::PointingHandCursor);
    m_PlaysBtn->setCheckable(true);
    m_PlaysBtn->setStyleSheet("QPushButton{background:#ffffff;color:#7c7085;border:node;border-top-right-radius:5;border-bottom-right-radius:5}\
                               QPushButton:hover{background:#f5f5f7}\
                               QPushButton:checked{background:#7c7085;color:#ffffff}");
    m_CloseBtn = new QPushButton(m_BtnFrame);
    m_CloseBtn->setGeometry(559,17,10,9);
    m_CloseBtn->setCursor(Qt::PointingHandCursor);
    m_CloseBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/SongList/closeList.png)}");

    mutexBtnGroup = new QButtonGroup(m_BtnFrame);
    //设置按钮互斥
    mutexBtnGroup->setExclusive(true);
    mutexBtnGroup->addButton(m_PlayingBtn);
    mutexBtnGroup->addButton(m_PlaysBtn);

    m_StatusFrmae = new QFrame;
    m_StatusFrmae->setFixedHeight(30);
    m_StatusFrmae->setStyleSheet("QFrame{background:#f9f9f9}");

    m_CountLabel = new QLabel("总0首",m_StatusFrmae);
    m_CountLabel->setGeometry(33,8,50,15);
    m_CountLabel->setStyleSheet("QLabel{border:node;color:#666666}");

    m_CollectBtn = new QPushButton(m_StatusFrmae);
    m_CollectBtn->setGeometry(418,8,67,13);
    m_CollectBtn->setCursor(Qt::PointingHandCursor);
    m_CollectBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/SongList/Collect.png)}");

    m_LineLabel = new QLabel("|",m_StatusFrmae);
    m_LineLabel->setGeometry(496,10,1,10);

    m_EmptyBtn = new QPushButton(m_StatusFrmae);
    m_EmptyBtn->setGeometry(507,8,41,14);
    m_EmptyBtn->setCursor(Qt::PointingHandCursor);
    m_EmptyBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/SongList/Empty.png)}");

    m_StackWin = new QStackedWidget;

    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->addWidget(m_BtnFrame);
    m_vMainLayout->addWidget(m_StatusFrmae);
    m_vMainLayout->addWidget(m_StackWin);
    m_vMainLayout->setMargin(0);
    m_vMainLayout->setSpacing(0);
}

void SongListFrame::initPlayList()
{
    m_PlayingList = new QListWidget;
    m_PlayingList->setAlternatingRowColors(true);//设置交替行颜色

    m_PlaysList = new QListWidget;

    m_StackWin->addWidget(m_PlayingList);
    m_StackWin->addWidget(m_PlaysList);
}

void SongListFrame::initConnect()
{
    //按钮切换Stack窗口
    m_signalMapper = new QSignalMapper(this);
    connect(m_PlayingBtn,SIGNAL(clicked()),m_signalMapper,SLOT(map()));
    m_signalMapper->setMapping(m_PlayingBtn,0);

    connect(m_PlaysBtn,SIGNAL(clicked()),m_signalMapper,SLOT(map()));
    m_signalMapper->setMapping(m_PlaysBtn,1);

    connect(m_signalMapper,SIGNAL(mapped(int)),m_StackWin,SLOT(setCurrentIndex(int)));

    //隐藏窗口
    connect(m_CloseBtn, SIGNAL(clicked(bool)),this,SLOT(hide()));

    connect(m_PlayingBtn, SIGNAL(clicked(bool)),this,SLOT(slot_ShowHideBtn()));
    connect(m_PlaysBtn, SIGNAL(clicked(bool)),this,SLOT(slot_ShowHideBtn()));
}

//show/hide 收藏按钮和竖线文本
void SongListFrame::slot_ShowHideBtn()
{
    if(m_PlayingBtn == reinterpret_cast<QPushButton*>(sender()))
    {
        m_CollectBtn->show();
        m_LineLabel->show();
    }
    if(m_PlaysBtn == reinterpret_cast<QPushButton*>(sender()))
    {
        m_CollectBtn->hide();
        m_LineLabel->hide();
    }
}


