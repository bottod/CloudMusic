#include "ListWidgetFindMusic.h"
#include <QPainter>

ListWidgetFindMusic::ListWidgetFindMusic(QWidget *parent) : QWidget(parent)
{
    init();
}

void ListWidgetFindMusic::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(225,225,225));
    p.drawLine(30,40,width()-30,40);
}

void ListWidgetFindMusic::init()
{
    findMusicStack = new QStackedWidget;

    recommendBtn = new QPushButton("个性推荐");
    recommendBtn->setFixedSize(60,40);
    recommendBtn->setCheckable(true);
    recommendBtn->setChecked(true);
    recommendBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/0/btn_normal_mask.png);color:rgb(68,68,68);font-size:15px}\
                                QPushButton:hover{color:rgb(102,183,255);}\
                                QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    songListBtn = new QPushButton("歌单");
    songListBtn->setFixedSize(60,40);
    songListBtn->setCheckable(true);
    songListBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/0/btn_normal_mask.png);color:rgb(68,68,68);font-size:15px}\
                                QPushButton:hover{color:rgb(102,183,255);}\
                                QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    radioBtn = new QPushButton("主播电台");
    radioBtn->setFixedSize(60,40);
    radioBtn->setCheckable(true);
    radioBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/0/btn_normal_mask.png);color:rgb(68,68,68);font-size:15px}\
                             QPushButton:hover{color:rgb(102,183,255);}\
                             QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    rankBtn = new QPushButton("排行榜");
    rankBtn->setFixedSize(60,40);
    rankBtn->setCheckable(true);
    rankBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/0/btn_normal_mask.png);font-size:15px}\
                            QPushButton:hover{color:rgb(102,183,255);}\
                            QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    singleBtn = new QPushButton("歌手");
    singleBtn->setFixedSize(60,40);
    singleBtn->setCheckable(true);
    singleBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/0/btn_normal_mask.png);color:rgb(68,68,68);font-size:15px}\
                              QPushButton:hover{color:rgb(102,183,255);}\
                              QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    newMusicBtn = new QPushButton("最新音乐");
    newMusicBtn->setFixedSize(60,40);
    newMusicBtn->setCheckable(true);
    newMusicBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/0/btn_normal_mask.png);color:rgb(68,68,68);font-size:15px}\
                                QPushButton:hover{color:rgb(102,183,255);}\
                                QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    m_btnVec_FindMusic<<recommendBtn<<songListBtn<<radioBtn<<rankBtn<<singleBtn<<newMusicBtn;

    mutexBtnGroupFindMusic = new QButtonGroup(this);
    mutexBtnGroupFindMusic->setExclusive(true);

    for(int i=0; i<m_btnVec_FindMusic.count(); ++i)
    {
        mutexBtnGroupFindMusic->addButton(m_btnVec_FindMusic.at(i));
        connect(m_btnVec_FindMusic.at(i),&QPushButton::clicked,this,[=](){findMusicStack->setCurrentIndex(i);});
    }

    h_btnBarLayout = new QHBoxLayout;

    h_btnBarLayout->addStretch(165);
    h_btnBarLayout->addWidget(recommendBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(songListBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(radioBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(rankBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(singleBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(newMusicBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addStretch(165);
    h_btnBarLayout->setSpacing(20);
    h_btnBarLayout->setMargin(0);

    //personal widget
    personal_widget = new QWidget(this);
    QVBoxLayout * lay = new QVBoxLayout(personal_widget);
    m_animationFrame1 = new AnimationWidget(personal_widget);
    m_animationFrame2 = new AnimationWidget(personal_widget);
    lay->addWidget(m_animationFrame1);
    lay->addWidget(m_animationFrame2);


    findMusicStack->addWidget(personal_widget);
    findMusicStack->addWidget(new QLabel("window2",findMusicStack));
    findMusicStack->addWidget(new QLabel("window3",findMusicStack));
    findMusicStack->addWidget(new QLabel("window4",findMusicStack));
    findMusicStack->addWidget(new QLabel("window5",findMusicStack));
    findMusicStack->addWidget(new QLabel("window6",findMusicStack));

    v_mainLayout = new QVBoxLayout(this);
    v_mainLayout->addLayout(h_btnBarLayout);
    v_mainLayout->addWidget(findMusicStack);
    v_mainLayout->setMargin(0);
}
