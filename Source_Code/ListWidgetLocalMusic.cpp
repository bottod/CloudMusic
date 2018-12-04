#include "ListWidgetLocalMusic.h"

ListWidgetLocalMusic::ListWidgetLocalMusic(QWidget *parent) : QWidget(parent)
{
    localPlayList = new QMediaPlaylist(this);

    initTitle();
    initStack();

    m_MainLayout = new QVBoxLayout(this);
    m_MainLayout->addWidget(titleFrame);
    m_MainLayout->addWidget(localMusicStack);
}

void ListWidgetLocalMusic::initTitle()
{
    titleFrame = new QFrame(this);
    titleFrame->setFixedHeight(56);
    titleFrame->setStyleSheet("QFrame{border-color:rgb(225,225,225);border-width: 0 0 1 0;border-style: solid}");

    m_localLabel = new QLabel("本地音乐",this);
    m_localLabel->setStyleSheet("QLabel{border:none;font:20px}");
    m_localLabel->setFixedWidth(100);

    m_CountLabel = new QLabel("0首音乐,",this);
    m_CountLabel->resize(m_CountLabel->width(),m_CountLabel->height());
    m_CountLabel->setStyleSheet("QLabel{border:none}");

    m_selectBtn = new QPushButton("选择目录",this);
    m_selectBtn->adjustSize();
    m_selectBtn->setCursor(Qt::PointingHandCursor);
    m_selectBtn->setFlat(true);
    m_selectBtn->setStyleSheet("QPushButton{background-color:transparent;border:none;color:#0c73c2}");

    m_listBtn = new QPushButton(this);
    m_listBtn->setFixedSize(26,22);
    m_listBtn->setCursor(Qt::PointingHandCursor);
    m_listBtn->setCheckable(true);
    m_listBtn->setChecked(true);
    m_listBtn->setToolTip("列表");
    m_listBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/list.png)}\
                              QPushButton:checked{border-image:url(:/images/RightStack/4/list_checked.png)}");

    m_singalBtn = new QPushButton(this);
    m_singalBtn->setFixedSize(26,22);
    m_singalBtn->setCursor(Qt::PointingHandCursor);
    m_singalBtn->setCheckable(true);
    m_singalBtn->setToolTip("歌手");
    m_singalBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/singal.png)}\
                                QPushButton:checked{border-image:url(:/images/RightStack/4/singal_checked.png)}");
    m_cdBtn = new QPushButton(this);
    m_cdBtn->setFixedSize(26,22);
    m_cdBtn->setCursor(Qt::PointingHandCursor);
    m_cdBtn->setCheckable(true);
    m_cdBtn->setToolTip("专辑");
    m_cdBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/cd.png)}\
                            QPushButton:checked{border-image:url(:/images/RightStack/4/cd_checked.png)}");

    m_dirBtn = new QPushButton(this);
    m_dirBtn->setFixedSize(26,22);
    m_dirBtn->setCursor(Qt::PointingHandCursor);
    m_dirBtn->setCheckable(true);
    m_dirBtn->setToolTip("文件夹");
    m_dirBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/dir.png)}\
                             QPushButton:checked{border-image:url(:/images/RightStack/4/dir_checked.png)}");

    m_btnVec_LocalMusic<<m_listBtn<<m_singalBtn<<m_cdBtn<<m_dirBtn;

    mutexBtnGroupLocalMusic = new QButtonGroup(this);
    mutexBtnGroupLocalMusic->setExclusive(true);

    for(int i=0; i<m_btnVec_LocalMusic.count(); ++i)
    {
        mutexBtnGroupLocalMusic->addButton(m_btnVec_LocalMusic.at(i));
        connect(m_btnVec_LocalMusic.at(i),&QPushButton::clicked,this,[=](){localMusicStack->setCurrentIndex(i);});
    }

    hTitleLayout = new QHBoxLayout(titleFrame);
    hTitleLayout->addWidget(m_localLabel);
    hTitleLayout->addWidget(m_CountLabel);
    hTitleLayout->addWidget(m_selectBtn);
    hTitleLayout->addStretch();
    hTitleLayout->addWidget(m_listBtn);
    hTitleLayout->addWidget(m_singalBtn);
    hTitleLayout->addWidget(m_cdBtn);
    hTitleLayout->addWidget(m_dirBtn);
    hTitleLayout->setSpacing(0);

}

void ListWidgetLocalMusic::initStack()
{
    localMusicStack = new QStackedWidget(this);

    //-----------------------------------window1---------------------------------------;
    stackFrame1 = new QFrame(localMusicStack);
    stackFrame1Title = new QFrame(stackFrame1);

    m_playAllBtn = new QPushButton(stackFrame1Title);
    m_playAllBtn->setCursor(Qt::PointingHandCursor);
    m_playAllBtn->setFixedSize(91,26);
    m_playAllBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/PlayAll.png)}");

    m_addBtn = new QPushButton(stackFrame1Title);
    m_addBtn->setCursor(Qt::PointingHandCursor);
    m_addBtn->setFixedSize(32,26);
    m_addBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/Add.png)}");

    m_matchMusicBtn = new QPushButton(stackFrame1Title);
    m_matchMusicBtn->setCursor(Qt::PointingHandCursor);
    m_matchMusicBtn->setFixedSize(92,26);
    m_matchMusicBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/Match.png)}");

    m_searchEdit = new QLineEdit(stackFrame1Title);
    m_searchEdit->setFixedSize(172,24);
    m_searchEdit->setPlaceholderText("搜索本地音乐");
    m_searchEdit->setStyleSheet("QLineEdit{border-radius:10px;border-color:rgb(225,225,225);border-width: 1;border-style: solid}");

    m_searchLabel = new QLabel(stackFrame1Title);
    m_searchLabel->setFixedSize(13,14);
    m_searchLabel->setStyleSheet("QLabel{border-image:url(:/images/RightStack/4/search.png)}");

    QHBoxLayout *searchLayout = new QHBoxLayout(m_searchEdit);
    searchLayout->addStretch();
    searchLayout->addWidget(m_searchLabel);
    searchLayout->setSpacing(0);
    searchLayout->setContentsMargins(0,0,10,0);
    QMargins margins = m_searchEdit->textMargins();
    m_searchEdit->setTextMargins(margins.left()+10, margins.top(), m_searchLabel->width()+15, margins.bottom());

    hStackFrame1TitleLayout = new QHBoxLayout(stackFrame1Title);
    hStackFrame1TitleLayout->addWidget(m_playAllBtn);
    hStackFrame1TitleLayout->addWidget(m_addBtn);
    hStackFrame1TitleLayout->addSpacing(15);
    hStackFrame1TitleLayout->addWidget(m_matchMusicBtn);
    hStackFrame1TitleLayout->addStretch();
    hStackFrame1TitleLayout->addWidget(m_searchEdit);
    hStackFrame1TitleLayout->setSpacing(0);

    //title finish - content start
    m_StackFrame1TableWidget = new QTableWidget(stackFrame1);

    m_StackFrame1TableWidget->setColumnCount(6);
    QStringList header;
    header<<""<<" 音乐标题"<<" 歌手"<<" 专辑"<<" 时长"<<" 大小";
    m_StackFrame1TableWidget->setHorizontalHeaderLabels(header);

    m_StackFrame1TableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    m_StackFrame1TableWidget->horizontalHeader()->resizeSection(0,50);
    m_StackFrame1TableWidget->horizontalHeader()->resizeSection(1,180);
    m_StackFrame1TableWidget->horizontalHeader()->resizeSection(2,120);
    m_StackFrame1TableWidget->horizontalHeader()->resizeSection(3,180);
    m_StackFrame1TableWidget->horizontalHeader()->resizeSection(4,120);
    m_StackFrame1TableWidget->horizontalHeader()->setFixedHeight(30);
    m_StackFrame1TableWidget->horizontalHeader()->setStretchLastSection(true);
    m_StackFrame1TableWidget->horizontalHeader()->setHighlightSections(false);
    m_StackFrame1TableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_StackFrame1TableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#fafafa;color:#666666;border:1px solid #cccccc;}"
                                                           "QHeaderView::section::hover{background:#ecedee}");

    m_StackFrame1TableWidget->setStyleSheet("QTableWidget{color:#888888;selection-background-color:#e4e4e6}");

    m_StackFrame1TableWidget->verticalHeader()->setDefaultSectionSize(30);
    m_StackFrame1TableWidget->verticalHeader()->setVisible(false);
    m_StackFrame1TableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;width:10;height:150;}"
                                                            "QScrollBar::handle{background:#e1e1e2; border:2px solid transparent; border-radius:5px;}"
                                                            "QScrollBar::handle:hover{background:#cfcfd1;}"
                                                            "QScrollBar::sub-line{background:transparent;}"
                                                            "QScrollBar::add-line{background:transparent;}");

    m_StackFrame1TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_StackFrame1TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_StackFrame1TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_StackFrame1TableWidget->setFocusPolicy(Qt::NoFocus);
    m_StackFrame1TableWidget->setShowGrid(false);
    m_StackFrame1TableWidget->setAlternatingRowColors(true);
    m_StackFrame1TableWidget->setFrameShape(QFrame::NoFrame);

    QVBoxLayout *vStackFrame1Layout = new QVBoxLayout(stackFrame1);
    vStackFrame1Layout->addWidget(stackFrame1Title);
    vStackFrame1Layout->addWidget(m_StackFrame1TableWidget);
    vStackFrame1Layout->setMargin(0);
    vStackFrame1Layout->setSpacing(0);
    //-----------------------------------------------------------------------------------

    localMusicStack->addWidget(stackFrame1);
    localMusicStack->addWidget(new QLabel("window2",localMusicStack));
    localMusicStack->addWidget(new QLabel("window3",localMusicStack));
    localMusicStack->addWidget(new QLabel("window4",localMusicStack));
}
