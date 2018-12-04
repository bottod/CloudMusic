#include <QMenu>
#include <QFile>

#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) : QFrame(parent)
{
    setMouseTracking(true);
    initTitle();
}

void TitleBar::initTitle()
{
    setStyleSheet(::main_style);

    setMinimumSize(1000,50);
    setMaximumSize(1920,50);

    titleLayout = new QHBoxLayout(this);

    titleIconLabel = new QLabel;
    titleIconLabel->setFixedWidth(114);
    titleIconLabel->setCursor(Qt::PointingHandCursor);
    titleIconLabel->setPixmap(QPixmap(":/images/TitleBar/titleIcon.png"));


    LayoutLeft = new QHBoxLayout;

    leftBtn = new QPushButton;
    leftBtn->setStyleSheet("QPushButton{background:transparent;\
                           border-image:url(:/images/TitleBar/leftArrow.png);}");
    leftBtn->setFixedSize(27,22);
    leftBtn->setToolTip("后退");
    leftBtn->setDisabled(true);

    rightBtn = new QPushButton;
    rightBtn->setStyleSheet("QPushButton{background:transparent;\
                            border-image:url(:/images/TitleBar/rightArrow.png);}");
    rightBtn->setFixedSize(27,22);
    rightBtn->setToolTip("前进");
    rightBtn->setDisabled(true);

    searchEdit = new QLineEdit;
    searchEdit->setStyleSheet("QLineEdit{border-radius:10px;\
                              background:rgb(73,140,213);\
                              color:rgb(238,211,211);}");
    searchEdit->setFixedSize(220,20);
    searchEdit->setPlaceholderText("搜索音乐，歌手，歌词，用户");

    searchBtn = new QPushButton(searchEdit);
    searchBtn->setStyleSheet("QPushButton{background:transparent;\
                             border-image:url(:/images/TitleBar/search.png);}\
                             QPushButton::hover{border-image:url(:/images/TitleBar/search_hover.png);}");
    searchBtn->setFixedSize(13,12);
    searchBtn->setCursor(Qt::PointingHandCursor);

    QMargins margins = searchEdit->textMargins();
    searchEdit->setTextMargins(margins.left()+10, margins.top(), searchBtn->width()+15, margins.bottom());

    searchLayout = new QHBoxLayout(searchEdit);
    searchLayout->addStretch();
    searchLayout->addWidget(searchBtn);
    searchLayout->setSpacing(0);
    //btn at right
    searchLayout->setContentsMargins(0,0,10,0);

    LayoutLeft->addWidget(leftBtn);
    LayoutLeft->addWidget(rightBtn);
    LayoutLeft->addSpacing(10);
    LayoutLeft->addWidget(searchEdit);
    LayoutLeft->setSpacing(0);

    LayoutRight = new QHBoxLayout;

    userIconBtn = new QPushButton;
    userIconBtn->setCursor(Qt::PointingHandCursor);
    userIconBtn->setFixedSize(40,32);
    userIconBtn->setStyleSheet("QPushButton{background:transparent;\
                               border-image:url(:/images/TitleBar/userIcon.png);}");

    loginBtn = new QPushButton;
    loginBtn->setText("未登录");
    loginBtn->setFlat(true);
    loginBtn->adjustSize();
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setStyleSheet("QPushButton{background:transparent;\
                            color:rgb(238,238,238);\
                            border:none;}");

    //for trigon list
    QMenu *loginMenu = new QMenu;
    loginBtn->setMenu(loginMenu);

    skinBtn = new QPushButton;
    skinBtn->setCursor(Qt::PointingHandCursor);
    skinBtn->setFixedSize(16,14);
    skinBtn->setStyleSheet("QPushButton{background:transparent;\
                           border-image:url(:/images/TitleBar/skin.png);}\
                            QPushButton::hover{border-image:url(:/images/TitleBar/skin_hover.png);}");

    mailBtn = new QPushButton;
    mailBtn->setCursor(Qt::PointingHandCursor);
    mailBtn->setFixedSize(16,12);
    mailBtn->setStyleSheet("QPushButton{background:transparent;\
                           border-image:url(:/images/TitleBar/mail.png);}\
                            QPushButton::hover{border-image:url(:/images/TitleBar/mail_hover.png);}");

    setBtn = new QPushButton;
    setBtn->setCursor(Qt::PointingHandCursor);
    setBtn->setFixedSize(15,16);
    setBtn->setStyleSheet("QPushButton{background:transparent;\
                          border-image:url(:/images/TitleBar/set.png);}\
                           QPushButton::hover{border-image:url(:/images/TitleBar/set_hover.png);}");

    nullLabel = new QLabel;
    nullLabel->setPixmap(QPixmap(":/images/TitleBar/line.png"));

    miniBtn = new QPushButton;
    miniBtn->setCursor(Qt::PointingHandCursor);
    miniBtn->setFixedSize(13,11);
    miniBtn->setToolTip("mini模式");
    miniBtn->setStyleSheet("QPushButton{background:transparent;\
                           border-image:url(:/images/TitleBar/mini.png);}\
                            QPushButton::hover{border-image:url(:/images/TitleBar/mini_hover.png);}");

    minimumBtn = new QPushButton;
    minimumBtn->setCursor(Qt::PointingHandCursor);
    minimumBtn->setToolTip("最小化");
    minimumBtn->setFixedSize(14,18);
    minimumBtn->setStyleSheet("QPushButton{background:transparent;\
                              border-image:url(:/images/TitleBar/minimum.png);}\
                               QPushButton::hover{border-image:url(:/images/TitleBar/minimum_hover.png);}");

    maximumBtn = new QPushButton;
    maximumBtn->setCursor(Qt::PointingHandCursor);
    maximumBtn->setFixedSize(14,11);
    maximumBtn->setObjectName("maximumBtn");
    maximumBtn->setStyleSheet("QPushButton{background:transparent;\
                              border-image:url(:/images/TitleBar/maximum.png);}\
                               QPushButton::hover{border-image:url(:/images/TitleBar/maximum_hover.png);}");


    closeBtn = new QPushButton;
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setFixedSize(12,11);
    closeBtn->setToolTip("关闭");
    closeBtn->setStyleSheet("QPushButton{background:transparent;\
                            border-image:url(:/images/TitleBar/close.png);}\
                             QPushButton::hover{border-image:url(:/images/TitleBar/close_hover.png);}");

    LayoutRight->setSpacing(0);
    LayoutRight->addWidget(userIconBtn);
    LayoutRight->addWidget(loginBtn);
    LayoutRight->addSpacing(20);
    LayoutRight->addWidget(skinBtn);
    LayoutRight->addSpacing(20);
    LayoutRight->addWidget(mailBtn);
    LayoutRight->addSpacing(20);
    LayoutRight->addWidget(setBtn);
    LayoutRight->addSpacing(15);
    LayoutRight->addWidget(nullLabel);
    LayoutRight->addSpacing(15);
    LayoutRight->addWidget(miniBtn);
    LayoutRight->addSpacing(10);
    LayoutRight->addWidget(minimumBtn);
    LayoutRight->addSpacing(10);
    LayoutRight->addWidget(maximumBtn);
    LayoutRight->addSpacing(10);
    LayoutRight->addWidget(closeBtn);

    titleLayout->addWidget(titleIconLabel);
    titleLayout->addSpacing(60);
    titleLayout->addLayout(LayoutLeft);
    titleLayout->addStretch();
    titleLayout->addLayout(LayoutRight);
}

