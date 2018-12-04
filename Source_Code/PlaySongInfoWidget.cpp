#include "PlaySongInfoWidget.h"

PlaySongInfoWidget::PlaySongInfoWidget(QWidget *parent) : QFrame(parent)
{
    setFixedHeight(60);
    setFixedWidth(200);

    //border-width:up right buttom left
    setStyleSheet("QFrame{background:rgb(246,246,248);border-color:rgb(225,225,225);border-width: 0px 1px 0px 1px;border-style: solid;}");

    initWidget();
}

PlaySongInfoWidget::~PlaySongInfoWidget()
{
}

void PlaySongInfoWidget::setSongText(QString song, QString single)
{
    QString show_song = "";
    QString show_single = "";

    if(song.length() > 7)
    {
        show_song = song.mid(0,6);
        show_song.append("...");
        songNameBtn->setText(show_song);
        songNameBtn->setToolTip(song);
    }
    else
    {
        songNameBtn->setText(song);
        songNameBtn->setToolTip(song);
    }

    if(single.length() > 7)
    {
        show_single = single.mid(0,6);
        show_single.append("...");
        singleNameBtn->setText(show_single);
        singleNameBtn->setToolTip(single);
    }
    else
    {
        singleNameBtn->setText(single);
        singleNameBtn->setToolTip(single);
    }
}

void PlaySongInfoWidget::initWidget()
{
    h_mainLayout = new QHBoxLayout(this);
    v_initLayout1 = new QVBoxLayout;
    v_initLayout2 = new QVBoxLayout;

    cdLabel = new ClickLabel(this);
    cdLabel->setFixedSize(60,60);
    cdLabel->setCursor(Qt::PointingHandCursor);
    cdLabel->setStyleSheet("QLabel{border-image:url(:/images/SongInfo/cdCover.png)}");

    songNameBtn = new QPushButton(this);
    songNameBtn->setFixedSize(100,20);
    songNameBtn->setCursor(Qt::PointingHandCursor);
    songNameBtn->setText("未知");
    songNameBtn->adjustSize();
    songNameBtn->setStyleSheet("QPushButton{background:transparent;border:none;font:13px}");

    singleNameBtn = new QPushButton(this);
    singleNameBtn->setFixedSize(100,20);
    singleNameBtn->setCursor(Qt::PointingHandCursor);
    singleNameBtn->setText("未知");
    singleNameBtn->adjustSize();
    singleNameBtn->setStyleSheet("QPushButton{background:transparent;border:none;font:13px}");

    v_initLayout1->addWidget(songNameBtn);
    v_initLayout1->addWidget(singleNameBtn);
    v_initLayout1->setMargin(0);

    loveBtn = new QPushButton(this);
    loveBtn->setCursor(Qt::PointingHandCursor);
    loveBtn->setFixedSize(14,12);
    loveBtn->setStyleSheet("QPushButton{border-image:url(:/images/SongInfo/love.png)}");

    shareBtn = new QPushButton(this);
    shareBtn->setCursor(Qt::PointingHandCursor);
    shareBtn->setFixedSize(13,14);
    shareBtn->setStyleSheet("QPushButton{border-image:url(:/images/SongInfo/share.png)}");

    v_initLayout2->addWidget(loveBtn);
    v_initLayout2->addWidget(shareBtn);
    v_initLayout2->setMargin(5);

    h_mainLayout->addWidget(cdLabel);
    h_mainLayout->addLayout(v_initLayout1);
    h_mainLayout->addLayout(v_initLayout2);
    h_mainLayout->setMargin(0);
}


