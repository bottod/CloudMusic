#include "BottomWidget.h"

#include "MiddleWidgetRightStack.h"

BottomWidget::BottomWidget(QWidget *parent) : QFrame(parent)
{
    setFixedHeight(50);

    setStyleSheet("QFrame{Background:rgb(246,246,248);border-color:rgb(225,225,225);border-width:1px;border-style: solid;}");

    setMouseTracking(true);

    initWidget();
}

void BottomWidget::initWidget()
{
    h_mainLayout = new QHBoxLayout(this);

    lastBtn = new QPushButton;
    lastBtn->setFixedSize(30,30);
    lastBtn->setCursor(Qt::PointingHandCursor);
    lastBtn->setToolTip(" 上一首");
    lastBtn->setIcon(QIcon(":/images/BottomPlay/last.png"));
    lastBtn->setIconSize(lastBtn->size());
    lastBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-radius:15px}");

    playBtn = new QPushButton;
    playBtn->setFixedSize(34,34);
    playBtn->setCursor(Qt::PointingHandCursor);
    playBtn->setToolTip(" 播放");
    playBtn->setIcon(QIcon(":/images/BottomPlay/play.png"));
    playBtn->setIconSize(lastBtn->size());
    playBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-radius:17px}");

    nextBtn = new QPushButton;
    nextBtn->setFixedSize(30,30);
    nextBtn->setCursor(Qt::PointingHandCursor);
    nextBtn->setToolTip(" 下一首");
    nextBtn->setIcon(QIcon(":/images/BottomPlay/next.png"));
    nextBtn->setIconSize(lastBtn->size());
    nextBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-radius:15px}");



    startTimeLabel = new QLabel("00:00");
    startTimeLabel->setFixedSize(37,15);

    playTimeSlider = new QSlider;
    playTimeSlider->setOrientation(Qt::Horizontal);
    playTimeSlider->setFixedHeight(14);
    playTimeSlider->setRange(0,200);
    playTimeSlider->setSingleStep(1);
    playTimeSlider->setStyleSheet("QSlider::groove:horizontal{height: 4px;background: rgb(102,183,255);}\
                                   QSlider::add-page:horizontal{background:#c2c2c4;}\
                                   QSlider::handle:horizontal{width: 14px;background: url(:/images/BottomPlay/curTimeHandle.png);margin: -5 0 -5 0;}");

    playTimeSlider->installEventFilter(this);

    endTimeLabel = new QLabel("00:00");
    endTimeLabel->setFixedSize(37,15);

    m_controlFrame = new QFrame;
    m_controlFrame->setStyleSheet("border:none");
    m_hControlLayout = new QHBoxLayout(m_controlFrame);
    m_hControlLayout->setSpacing(10);
    m_hControlLayout->setMargin(10);
    m_hControlLayout->addWidget(startTimeLabel,Qt::AlignVCenter);
    m_hControlLayout->addWidget(playTimeSlider,Qt::AlignVCenter);
    m_hControlLayout->addWidget(endTimeLabel,Qt::AlignVCenter);




    volumeBtn = new QPushButton;
    volumeBtn->setFixedSize(16,12);
    volumeBtn->setCursor(Qt::PointingHandCursor);
    volumeBtn->setToolTip(" 静音 ");
    volumeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/volume.png)}");

    volumeSlider = new QSlider;
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setFixedSize(100,12);
    volumeSlider->setToolTip(" 音量调节");
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setSingleStep(1);
    volumeSlider->setStyleSheet("QSlider::groove:horizontal{height: 4px;background: rgb(102,183,255);}\
                                 QSlider::add-page:horizontal{background:#c2c2c4;}\
                                 QSlider::handle:horizontal{width: 12px;background: url(:/images/BottomPlay/volumeHandle.png);margin: -4 0 -4 0}");
    volumeSlider->installEventFilter(this);


    playModeBtn = new QPushButton;
    playModeBtn->setFixedSize(17,14);
    playModeBtn->setCursor(Qt::PointingHandCursor);
    playModeBtn->setToolTip(" 顺序播放 ");
    playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Sequential.png)}");

    lyricBtn = new QPushButton;
    lyricBtn->setFixedSize(16,16);
    lyricBtn->setCursor(Qt::PointingHandCursor);
    lyricBtn->setToolTip(" 打开歌词 ");
    lyricBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/lyric.png)}");

    listBtn = new QPushButton;
    listBtn->setFixedSize(19,17);
    listBtn->setCursor(Qt::PointingHandCursor);
    listBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/currentList.png)}");

    bottomRightLabel = new QLabel(this);
    bottomRightLabel->setPixmap(QPixmap(":images/BottomPlay/BottomRight.png"));
    bottomRightLabel->setAttribute(Qt::WA_TranslucentBackground);

    h_mainLayout->addWidget(lastBtn,Qt::AlignVCenter);
    h_mainLayout->addSpacing(10);
    h_mainLayout->addWidget(playBtn,Qt::AlignVCenter);
    h_mainLayout->addSpacing(10);
    h_mainLayout->addWidget(nextBtn,Qt::AlignVCenter);
    h_mainLayout->addWidget(m_controlFrame,Qt::AlignVCenter);
    h_mainLayout->addWidget(volumeBtn,Qt::AlignVCenter);
    h_mainLayout->addWidget(volumeSlider,Qt::AlignVCenter);
    h_mainLayout->addWidget(playModeBtn,Qt::AlignVCenter);
    h_mainLayout->addWidget(lyricBtn,Qt::AlignVCenter);
    h_mainLayout->addWidget(listBtn,Qt::AlignVCenter);
    h_mainLayout->setMargin(10);
    h_mainLayout->setSpacing(10);
}

void BottomWidget::paintEvent(QPaintEvent *)
{
    bottomRightLabel->setGeometry(width()-13,height()-13,10,10);
}

bool BottomWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==playTimeSlider || obj==volumeSlider)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            QSlider *slider = static_cast<QSlider*>(obj);
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                int dur = slider->maximum() - slider->minimum();
                int pos = slider->minimum() + static_cast<int>(dur * mouseEvent->x() / slider->width());
                if(pos != slider->sliderPosition())
                {
                    slider->setValue(pos);
                }
            }
        }
    }
    return QObject::eventFilter(obj,event);
}

