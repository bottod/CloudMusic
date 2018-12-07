#include "MainWidget.h"
#include <QtMath>
#include <QListWidgetItem>
#include <QTime>

MainWidget::MainWidget(QWidget *parent)
    : FramelessWidget(parent)
{

    setMinimumSize(1000,680);
    setFocus();

    //qRegisterMetaType<QVector<QStringList>>("QVector<QStringList>");

    //init title bar
    m_TitleBar = new TitleBar(this);
    connect(m_TitleBar->miniBtn,&QPushButton::clicked,this,&MainWidget::slot_showMiniWidget);
    connect(m_TitleBar->minimumBtn,&QPushButton::clicked,this,&MainWidget::showMinimized);
    connect(m_TitleBar->maximumBtn,&QPushButton::clicked,this,&MainWidget::slot_showMaximized);
    connect(m_TitleBar->closeBtn, &QPushButton::clicked,this,&MainWidget::slot_quitOrhide);

    m_MiddleWidget = new MiddleWidget(this);
    connect(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget,&QTableWidget::itemDoubleClicked,this,&MainWidget::slot_PlayLocalMusic);

    m_BottomWidget = new BottomWidget(this);
    connect(m_BottomWidget->listBtn,&QPushButton::clicked,this,&MainWidget::slot_showSongListWidget);
    connect(m_BottomWidget->playBtn,&QPushButton::clicked,this,&MainWidget::slot_playPause);
    connect(m_BottomWidget->playModeBtn,&QPushButton::clicked,this,&MainWidget::slot_playModeChange);
    connect(m_BottomWidget->playTimeSlider,&QSlider::valueChanged,this,&MainWidget::slot_setPosition);
    connect(m_BottomWidget->volumeBtn,&QPushButton::clicked,this,&MainWidget::slot_silence);
    connect(m_BottomWidget->nextBtn,&QPushButton::clicked,this,&MainWidget::slot_playNext);
    connect(m_BottomWidget->lastBtn,&QPushButton::clicked,this,&MainWidget::slot_playPre);

    //init mini mode widget
    m_MiniWidget = new miniWidget;
    connect(m_MiniWidget->m_recoveryWinBtn,&QPushButton::clicked,this,&MainWidget::slot_showMainWidget);
    connect(m_MiniWidget->m_nextBtn,&QPushButton::clicked,this,&MainWidget::slot_playNext);
    connect(m_MiniWidget->m_preBtn,&QPushButton::clicked,this,&MainWidget::slot_playPre);
    connect(m_MiniWidget->m_playStateBtn,&QPushButton::clicked,this,&MainWidget::slot_playPause);
    connect(m_MiniWidget->m_volBtn,&QPushButton::clicked,this,&MainWidget::slot_silence);

    //add all widget to window(main layout)
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_TitleBar);
    mainLayout->addWidget(m_MiddleWidget);
    mainLayout->addWidget(m_BottomWidget);


    m_SongListFrame = new SongListFrame(this);
    m_SongListFrameX = this->width()-m_SongListFrame->width();
    m_SongListFrameY = this->height()-m_SongListFrame->height()-m_BottomWidget->height();
    m_SongListFrame->hide();
    connect(this, &MainWidget::sig_PosChange,this,&MainWidget::slot_changeSongListPos);


    //player
    player = new QMediaPlayer;
    connect(player, &QMediaPlayer::volumeChanged,m_BottomWidget->volumeSlider,&QSlider::setValue);
    connect(m_BottomWidget->volumeSlider,&QSlider::valueChanged,[&]()
    {
        player->setVolume(m_BottomWidget->volumeSlider->value());
        if(0 == player->volume())
        {
            m_BottomWidget->volumeBtn->setToolTip(" 静音 ");
            m_BottomWidget->volumeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/volumeSilence.png)}");
        }
        else
        {
            m_BottomWidget->volumeBtn->setToolTip(QString::number(curVolume,10));
            m_BottomWidget->volumeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/volume.png)}");
        }
    });
    connect(player, &QMediaPlayer::positionChanged,this,&MainWidget::slot_updatePosition);
    connect(player, &QMediaPlayer::durationChanged,this,&MainWidget::slot_updateDuration);
    connect(player, &QMediaPlayer::currentMediaChanged,this,&MainWidget::slot_updateSongInfo);


    //init system tray
    initSystemTray();


    //skin widget
    m_skinWidget = new SkinWidget(this);
    connect(m_TitleBar->skinBtn,&QPushButton::clicked,this,&MainWidget::slot_showSkinWidget);
    //when widget size changed
    connect(this, &MainWidget::sig_PosChange,[&]()
    {
        m_skinWidget->setGeometry(m_TitleBar->skinBtn->pos().x()-123, m_TitleBar->skinBtn->pos().y()+24, 260, 169);
    });
    for(int i=0; i<m_skinWidget->m_ClickLabelVec.size(); ++i)
        connect(m_skinWidget->m_ClickLabelVec.at(i),&ClickLabel::clicked,[=]()
        {
            widget_color = i;
            m_TitleBar->setStyleSheet("QFrame{background-color:"+m_skinWidget->color1_list[i]+";}");
            m_TitleBar->searchEdit->setStyleSheet("QLineEdit{border-radius:10px;\
                                                  background:"+m_skinWidget->color2_list[i]+";\
                                                  color:rgb(238,211,211);}");

            m_MiniWidget->setStyleSheet("QFrame{background-color:"+m_skinWidget->color1_list[i]+";}");

            m_BottomWidget->lastBtn->setStyleSheet("QPushButton{background:"+m_skinWidget->color1_list[i]+";border-radius:15px}");
            m_BottomWidget->playBtn->setStyleSheet("QPushButton{background:"+m_skinWidget->color1_list[i]+";border-radius:15px}");
            m_BottomWidget->nextBtn->setStyleSheet("QPushButton{background:"+m_skinWidget->color1_list[i]+";border-radius:15px}");

            m_BottomWidget->playTimeSlider->setStyleSheet("QSlider::groove:horizontal{height: 4px;background: "+m_skinWidget->color1_list[i]+";}\
                                           QSlider::add-page:horizontal{background:#c2c2c4;}\
                                           QSlider::handle:horizontal{width: 14px;background: url(:/images/BottomPlay/curTimeHandle.png);margin: -5 0 -5 0;}");

            m_BottomWidget->volumeSlider->setStyleSheet("QSlider::groove:horizontal{height: 4px;background: "+m_skinWidget->color1_list[i]+";}\
                                       QSlider::add-page:horizontal{background:#c2c2c4;}\
                                       QSlider::handle:horizontal{width: 12px;background: url(:/images/BottomPlay/volumeHandle.png);margin: -4 0 -4 0}");

            m_skinWidget->hide();
        });


    //turntable widget
    m_turnTableLayoutWidget = new QWidget(this);
    m_turntableWidget = new TurntableWidget(m_turnTableLayoutWidget);
    //set layout widget's background color equal to m_turntableWidget background color
    QPalette background_palette;
    background_palette.setColor(QPalette::Background,m_turntableWidget->backgroud_color);
    m_turnTableLayoutWidget->setPalette(background_palette);
    m_turnTableLayoutWidget->setAutoFillBackground(true);
    m_turnTableLayoutWidget->hide();
    //set layout widget's layout
    QHBoxLayout *h_turnTable_layout = new QHBoxLayout(m_turnTableLayoutWidget);
    h_turnTable_layout->addStretch();
    h_turnTable_layout->addWidget(m_turntableWidget);
    h_turnTable_layout->addStretch();
    connect(this,&MainWidget::sig_PosChange,m_turnTableLayoutWidget,[&]()
    {
        m_turnTableLayoutWidget->setGeometry(m_MiddleWidget->x(),m_MiddleWidget->y(),m_MiddleWidget->width(),m_MiddleWidget->height());
    });
    connect(m_MiddleWidget->m_PlaySongInfoWidget->cdLabel,&ClickLabel::clicked,this,&MainWidget::slot_showTurnTableWidget);
    connect(m_turntableWidget->hideButton,&QPushButton::clicked,this,&MainWidget::slot_hideTurnTableWidget);


    readSettings();
}

MainWidget::~MainWidget()
{
    player->~QMediaPlayer();
    m_MiniWidget->~miniWidget();
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(QRect(0,0,m_TitleBar->width(),m_TitleBar->height()).contains(event->pos()) ||
       QRect(width()-13,height()-13,15,15).contains(event->pos()))
    {
        FramelessWidget::mousePressEvent(event);
    }
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(QRect(0,0,m_TitleBar->width(),m_TitleBar->height()).contains(event->pos()))
    {
        //avoid that list frame's pos become strange
        if(m_SongListFrame->isVisible())
            m_SongListFrame->hide();

        if(m_skinWidget->isVisible())
            m_skinWidget->hide();

        if(m_turnTableLayoutWidget->isVisible())
            m_turnTableLayoutWidget->hide();

        if(isMaximun)
        {
            isMaximun = false;
            showNormal();
            m_TitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/images/TitleBar/maximum.png);} \
                                                  QPushButton:hover{border-image:url(:/images/TitleBar/maximum_hover.png);}");
            m_TitleBar->maximumBtn->setToolTip("最大化");
        }
        else
        {
            isMaximun = true;
            showMaximized();
            m_TitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/images/TitleBar/maximum_cancel.png);} \
                                                  QPushButton:hover{border-image:url(:/images/TitleBar/maximum_cancel_hover.png);}");
            m_TitleBar->maximumBtn->setToolTip("向下还原");
        }


    }
}

//close mini and open main
void MainWidget::slot_showMainWidget()
{
    m_MiniWidget->hide();
    this->showNormal();
    m_TrayMenu->windowStyleMenu->setTitle("完整模式");
}

//quit or hide
void MainWidget::slot_quitOrhide()
{
    if(isFirstOpen)
    {
        /**************************dialog start************************/
        QDialog *close_dialog = new QDialog;
        close_dialog->setFixedSize(300,250);
        close_dialog->setStyleSheet("QDialog{background:rgb(179, 217, 255);border-image:url(:/images/closedialog.png);}");

        QHBoxLayout *tip_group = new QHBoxLayout();
        QLabel *tip_label = new QLabel("默认设置可于 ~/.config/Cloudmusic 修改",close_dialog);
        tip_label->setStyleSheet("background-color: rgb(166, 166, 166, 60)");
        tip_group->addWidget(tip_label);

        QVBoxLayout *radio_group = new QVBoxLayout();
        QButtonGroup *close_radio = new QButtonGroup(close_dialog);
        close_radio->setExclusive(true);
        QRadioButton *quit_button = new QRadioButton("退出程序",close_dialog);
        QRadioButton *hide_button = new QRadioButton("最小化到托盘",close_dialog);
        radio_group->addWidget(quit_button);
        radio_group->addWidget(hide_button);
        close_radio->addButton(quit_button);
        close_radio->addButton(hide_button);
        quit_button->setChecked(true);

        QCheckBox *default_check = new QCheckBox("设置为默认(下次不再提示)",close_dialog);

        QHBoxLayout *btn_group = new QHBoxLayout();
        QPushButton *ok_btn = new QPushButton("确定",close_dialog);
        ok_btn->setStyleSheet("QPushButton{background:rgb(102,183,255,70);}");
        connect(ok_btn,&QPushButton::clicked,[&](){close_dialog->done(QDialog::Accepted);});
        QPushButton *cancel_btn = new QPushButton("取消",close_dialog);
        cancel_btn->setStyleSheet("QPushButton{background:rgb(102,183,255,70);}");
        connect(cancel_btn,&QPushButton::clicked,[&](){close_dialog->done(QDialog::Rejected);});
        btn_group->addWidget(ok_btn);
        btn_group->addSpacing(10);
        btn_group->addWidget(cancel_btn);

        QVBoxLayout *dialog_main = new QVBoxLayout(close_dialog);
        dialog_main->addLayout(tip_group);
        dialog_main->addSpacing(20);
        dialog_main->addLayout(radio_group);
        dialog_main->addSpacing(20);
        dialog_main->addWidget(default_check);
        dialog_main->addSpacing(10);
        dialog_main->addLayout(btn_group);


        //start exec
        int result = close_dialog->exec();
        switch(result)
        {
            case QDialog::Accepted:
            {
                if(default_check->isChecked())
                    isFirstOpen = false;  //must be false; not show dialog

                if(quit_button->isChecked())
                {
                    isQuitHide = true;
                    if(!isMaximun)
                    {
                        QPoint pos = this->pos();
                        QSize size = this->size();
                        this->setMinimumSize(0,0);
                        QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
                        animation->setDuration(500);
                        animation->setStartValue(geometry());
                        animation->setEndValue(QRect(geometry().x(),geometry().y(),geometry().width(),0));
                        animation->setEasingCurve(QEasingCurve::InOutQuad);
                        connect(animation,&QPropertyAnimation::finished,[=](){hide();resize(size);move(pos);close();});
                        animation->start(QAbstractAnimation::DeleteWhenStopped);
                    }
                    else
                    {
                        close();
                    }
                }
                else if(hide_button->isChecked())
                {
                    isQuitHide = false;
                    if(!isMaximun)
                    {
                        QPoint pos = this->pos();
                        QSize size = this->size();
                        this->setMinimumSize(0,0);
                        QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
                        animation->setDuration(500);
                        animation->setStartValue(geometry());
                        animation->setEndValue(QRect(geometry().x(),geometry().y(),geometry().width(),0));
                        animation->setEasingCurve(QEasingCurve::InOutQuad);
                        connect(animation,&QPropertyAnimation::finished,[=](){hide();resize(size);move(pos);setMinimumSize(1000,680);});
                        animation->start(QAbstractAnimation::DeleteWhenStopped);
                    }
                    else
                    {
                        hide();
                    }
                }

            }
                break;
            default:
                break;
        }
        /**************************dialog end************************/
    }
    else
    {
        if(isQuitHide)
        {
            if(!isMaximun)
            {
                QPoint pos = this->pos();
                QSize size = this->size();
                this->setMinimumSize(0,0);
                QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
                animation->setDuration(500);
                animation->setStartValue(geometry());
                animation->setEndValue(QRect(geometry().x(),geometry().y(),geometry().width(),0));
                animation->setEasingCurve(QEasingCurve::InOutQuad);
                connect(animation,&QPropertyAnimation::finished,[=](){hide();resize(size);move(pos);close();});
                animation->start(QAbstractAnimation::DeleteWhenStopped);
            }
            else
            {
                close();
            }
        }
        else
        {
            if(!isMaximun)
            {
                QPoint pos = this->pos();
                QSize size = this->size();
                this->setMinimumSize(0,0);
                QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
                animation->setDuration(500);
                animation->setStartValue(geometry());
                animation->setEndValue(QRect(geometry().x(),geometry().y(),geometry().width(),0));
                animation->setEasingCurve(QEasingCurve::InOutQuad);
                connect(animation,&QPropertyAnimation::finished,[=](){hide();resize(size);move(pos);setMinimumSize(1000,680);});
                animation->start(QAbstractAnimation::DeleteWhenStopped);
            }
            else
            {
                hide();
            }
        }
    }

}

//close main and open mini
void MainWidget::slot_showMiniWidget()
{
    this->hide();
    m_MiniWidget->showNormal();
    m_TrayMenu->windowStyleMenu->setTitle("mini模式");
}

//max window and normal window
void MainWidget::slot_showMaximized()
{
    //avoid that list frame's pos become strange
    if(m_SongListFrame->isVisible())
        m_SongListFrame->hide();

    if(m_skinWidget->isVisible())
        m_skinWidget->hide();

    if(m_turnTableLayoutWidget->isVisible())
        m_turnTableLayoutWidget->hide();

    if(isMaximun)
    {
        isMaximun = false;
        showNormal();
        m_TitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/images/TitleBar/maximum.png);} \
                                              QPushButton:hover{border-image:url(:/images/TitleBar/maximum_hover.png);}");
        m_TitleBar->maximumBtn->setToolTip("最大化");
    }
    else
    {
        isMaximun = true;
        showMaximized();
        m_TitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/images/TitleBar/maximum_cancel.png);} \
                                              QPushButton:hover{border-image:url(:/images/TitleBar/maximum_cancel_hover.png);}");
        m_TitleBar->maximumBtn->setToolTip("向下还原");
    }

}

//skin widget
void MainWidget::slot_showSkinWidget()
{
    if(m_skinWidget->isVisible())
        m_skinWidget->hide();
    else
    {
        m_skinWidget->setGeometry(m_TitleBar->skinBtn->pos().x()-123, m_TitleBar->skinBtn->pos().y()+24, 260, 169);
        m_skinWidget->show();
        m_skinWidget->raise();
    }
}

//show turntable widget
void MainWidget::slot_showTurnTableWidget()
{
    m_turnTableLayoutWidget->show();
    QPropertyAnimation *animation=new QPropertyAnimation(m_turnTableLayoutWidget,"geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(m_MiddleWidget->x(),m_MiddleWidget->y()+m_MiddleWidget->height(),m_MiddleWidget->width(),0));
    animation->setEndValue(QRect(m_MiddleWidget->x(),m_MiddleWidget->y(),m_MiddleWidget->width(),m_MiddleWidget->height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//hide turntable widget
void MainWidget::slot_hideTurnTableWidget()
{
    m_turnTableLayoutWidget->show();
    QPropertyAnimation *animation=new QPropertyAnimation(m_turnTableLayoutWidget,"geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(m_MiddleWidget->x(),m_MiddleWidget->y(),m_MiddleWidget->width(),m_MiddleWidget->height()));
    animation->setEndValue(QRect(m_MiddleWidget->x(),m_MiddleWidget->y()+m_MiddleWidget->height(),m_MiddleWidget->width(),0));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//play and pause btn
void MainWidget::slot_playPause()
{
    //songlist must have item
    if(m_SongListFrame->m_PlayingList->count() != 0)
    {
        if(isMediaPlay)
        {
            isMediaPlay = false;
            player->pause();
            m_BottomWidget->playBtn->setToolTip("播放");
            m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/play.png"));
            m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
            m_TrayMenu->pauseAction->setText("播放");
            m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/play.png"));
            m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/play.png);}");

            m_turntableWidget->record_timer->stop();
            m_turntableWidget->update_stylus_out();
        }
        else
        {
            isMediaPlay = true;
            player->play();
            m_BottomWidget->playBtn->setToolTip("暂停");
            m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/pause.png"));
            m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
            m_TrayMenu->pauseAction->setText("暂停");
            m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));
            m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png);}");

            m_turntableWidget->record_timer->start();
            m_turntableWidget->stylus_in_timer->start();
        }
    }
}

//play mode set
void MainWidget::slot_playModeChange()
{
    switch (playMode)
    {
        case 0:
            ++playMode;
            m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Loop.png)}");
            m_BottomWidget->playModeBtn->setToolTip("列表循环");
            m_TrayMenu->playModeMenu->setTitle("列表循环");
            m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Loop);
            break;
        case 1:
            ++playMode;
            m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/CurrentItemInLoop.png)}");
            m_BottomWidget->playModeBtn->setToolTip("单曲循环");
            m_TrayMenu->playModeMenu->setTitle("单曲循环");
            m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            break;
        case 2:
            ++playMode;
            m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Random.png)}");
            m_BottomWidget->playModeBtn->setToolTip("随机播放");
            m_TrayMenu->playModeMenu->setTitle("随机播放");
            m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Random);
            break;
        case 3:
            playMode = 0;
            m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Sequential.png)}");
            m_BottomWidget->playModeBtn->setToolTip("顺序播放");
            m_TrayMenu->playModeMenu->setTitle("顺序播放");
            m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
            break;
        default:
            break;
    }
}

void MainWidget::initSystemTray()
{
    m_SystemTray = new QSystemTrayIcon(this);
    m_TrayMenu = new TrayIconMenu(this);

    m_SystemTray->setContextMenu(m_TrayMenu);
    m_SystemTray->setToolTip(" 未知 - 未知 ");
    m_SystemTray->setIcon(QIcon(":/images/TrayIcon/logoTrayIcon.png"));

    m_SystemTray->show();
    connect(m_SystemTray, &QSystemTrayIcon::activated, this, &MainWidget::slot_onActivated);

    connect(m_TrayMenu->pauseAction,&QAction::triggered,[&]()
    {
        //songlist must have item
        if(m_SongListFrame->m_PlayingList->count() != 0)
        {
            if(isMediaPlay)
            {
                isMediaPlay = false;
                player->pause();
                m_BottomWidget->playBtn->setToolTip("播放");
                m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/play.png"));
                m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
                m_TrayMenu->pauseAction->setText("播放");
                m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/play.png"));
                m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/play.png);}");

                m_turntableWidget->record_timer->stop();
                m_turntableWidget->update_stylus_out();
            }
            else
            {
                isMediaPlay = true;
                player->play();
                m_BottomWidget->playBtn->setToolTip("暂停");
                m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/pause.png"));
                m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
                m_TrayMenu->pauseAction->setText("暂停");
                m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));
                m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png);}");

                m_turntableWidget->record_timer->start();
                m_turntableWidget->stylus_in_timer->start();
            }
        }
    });

    connect(m_TrayMenu->nextAction,&QAction::triggered,this,&MainWidget::slot_playNext);
    connect(m_TrayMenu->lastAction,&QAction::triggered,this,&MainWidget::slot_playPre);

    connect(m_TrayMenu->playMode_Sequential_Action,&QAction::triggered,[&]()
    {
      playMode = 0;
      m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Sequential.png)}");
      m_BottomWidget->playModeBtn->setToolTip("顺序播放");
      m_TrayMenu->playModeMenu->setTitle("顺序播放");
      m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
    });
    connect(m_TrayMenu->playMode_Loop_Action,&QAction::triggered,[&]()
    {
      playMode = 1;
      m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Loop.png)}");
      m_BottomWidget->playModeBtn->setToolTip("列表循环");
      m_TrayMenu->playModeMenu->setTitle("列表循环");
      m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    });
    connect(m_TrayMenu->playMode_CurrentItemInLoop_Action,&QAction::triggered,[&]()
    {
      playMode = 2;
      m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/CurrentItemInLoop.png)}");
      m_BottomWidget->playModeBtn->setToolTip("单曲循环");
      m_TrayMenu->playModeMenu->setTitle("单曲循环");
      m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    });
    connect(m_TrayMenu->playMode_Random_Action,&QAction::triggered,[&]()
    {
      playMode = 3;
      m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Random.png)}");
      m_BottomWidget->playModeBtn->setToolTip("随机播放");
      m_TrayMenu->playModeMenu->setTitle("随机播放");
      m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Random);
    });


    connect(m_TrayMenu->mini_Window_Action,&QAction::triggered,this,&MainWidget::slot_showMiniWidget);
    connect(m_TrayMenu->complete_Window_Action,&QAction::triggered,this,&MainWidget::slot_showMainWidget);

    connect(m_TrayMenu->quitAction,&QAction::triggered,this,&MainWidget::close);
}

void MainWidget::slot_onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
        {
            if(m_MiniWidget->isVisible())
            {
                m_MiddleWidget->show();
            }
            else
            {
                show();
                raise();
                activateWindow();
            }
            break;
        }
        case QSystemTrayIcon::MiddleClick:
        {
            break;
        }
        case QSystemTrayIcon::DoubleClick:
        {
            break;
        }
        default:
            break;
    }
}

void MainWidget::writeSettings()
{
    QSettings settings;

    settings.setValue("pos", pos());
    settings.setValue("size", size());

    settings.beginGroup("main_setting");
    settings.setValue("first_open", isFirstOpen);
    settings.setValue("quit_hide", isQuitHide);//quit:true  |  hide:false
    settings.setValue("is_max",isMaximun);
    settings.setValue("play_mode",playMode);
    curVolume = player->volume();
    settings.setValue("volume",curVolume);
    settings.setValue("widget_color",widget_color);
    settings.endGroup();

    settings.beginGroup("mini_widget");
    settings.setValue("pos", m_MiniWidget->pos());
    settings.endGroup();

}

void MainWidget::readSettings()
{
    QSettings settings;

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(1000, 600)).toSize();
    move(pos);
    resize(size);

    //main_setting
    settings.beginGroup("main_setting");
    isFirstOpen = settings.value("first_open",true).toBool();
    isQuitHide = settings.value("quit_hide",true).toBool();

    isMaximun = settings.value("is_max",false).toBool();
    if(isMaximun)
    {
        m_TitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/images/TitleBar/maximum_cancel.png);} \
                                              QPushButton:hover{border-image:url(:/images/TitleBar/maximum_cancel_hover.png);}");
        m_TitleBar->maximumBtn->setToolTip("向下还原");
    }
    else
    {
        m_TitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/images/TitleBar/maximum.png);} \
                                              QPushButton:hover{border-image:url(:/images/TitleBar/maximum_hover.png);}");
        m_TitleBar->maximumBtn->setToolTip("最大化");
    }

    playMode = settings.value("play_mode",0).toInt();
    switch (playMode)
    {
      case 0:
          m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Sequential.png)}");
          m_BottomWidget->playModeBtn->setToolTip("顺序播放");
          m_TrayMenu->playModeMenu->setTitle("顺序播放");
          m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
          break;
      case 1:
          m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Loop.png)}");
          m_BottomWidget->playModeBtn->setToolTip("列表循环");
          m_TrayMenu->playModeMenu->setTitle("列表循环");
          m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Loop);
          break;
      case 2:
          m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/CurrentItemInLoop.png)}");
          m_BottomWidget->playModeBtn->setToolTip("单曲循环");
          m_TrayMenu->playModeMenu->setTitle("单曲循环");
          m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
          break;
      case 3:
          m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Random.png)}");
          m_BottomWidget->playModeBtn->setToolTip("随机播放");
          m_TrayMenu->playModeMenu->setTitle("随机播放");
          m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Random);
          break;
      default:
          break;
    }
    curVolume = settings.value("volume",50).toInt();
    player->setVolume(curVolume);

    widget_color = settings.value("widget_color",-1).toInt();
    if(widget_color != -1)
    {
        m_TitleBar->setStyleSheet("QFrame{background-color:"+m_skinWidget->color1_list[widget_color]+";}");
        m_TitleBar->searchEdit->setStyleSheet("QLineEdit{border-radius:10px;\
                                              background:"+m_skinWidget->color2_list[widget_color]+";\
                                              color:rgb(238,211,211);}");

        m_MiniWidget->setStyleSheet("QFrame{background-color:"+m_skinWidget->color1_list[widget_color]+";}");

        m_BottomWidget->lastBtn->setStyleSheet("QPushButton{background:"+m_skinWidget->color1_list[widget_color]+";border-radius:15px}");
        m_BottomWidget->playBtn->setStyleSheet("QPushButton{background:"+m_skinWidget->color1_list[widget_color]+";border-radius:15px}");
        m_BottomWidget->nextBtn->setStyleSheet("QPushButton{background:"+m_skinWidget->color1_list[widget_color]+";border-radius:15px}");

        m_BottomWidget->playTimeSlider->setStyleSheet("QSlider::groove:horizontal{height: 4px;background: "+m_skinWidget->color1_list[widget_color]+";}\
                                       QSlider::add-page:horizontal{background:#c2c2c4;}\
                                       QSlider::handle:horizontal{width: 14px;background: url(:/images/BottomPlay/curTimeHandle.png);margin: -5 0 -5 0;}");

        m_BottomWidget->volumeSlider->setStyleSheet("QSlider::groove:horizontal{height: 4px;background: "+m_skinWidget->color1_list[widget_color]+";}\
                                   QSlider::add-page:horizontal{background:#c2c2c4;}\
                                   QSlider::handle:horizontal{width: 12px;background: url(:/images/BottomPlay/volumeHandle.png);margin: -4 0 -4 0}");
    }
    settings.endGroup();
    //---------------------------------------------

    settings.beginGroup("mini_widget");
    QPoint mini_pos = settings.value("pos", QPoint(1200, 100)).toPoint();
    settings.endGroup();
    m_MiniWidget->move(mini_pos);
}

//when change window size (framelesswidget signal)
void MainWidget::slot_changeSongListPos(int newWidth, int newHeight)
{
    m_SongListFrameX = newWidth-m_SongListFrame->width();
    m_SongListFrameY = newHeight-m_SongListFrame->height()-m_BottomWidget->height();
    if(m_SongListFrameX<=420)
        m_SongListFrameX=420;

    if(m_SongListFrameY<=160)
        m_SongListFrameY=160;

    m_SongListFrame->move(m_SongListFrameX, m_SongListFrameY);
}

//when click list button
void MainWidget::slot_showSongListWidget()
{
    if(m_SongListFrame->isVisible())
        m_SongListFrame->hide();
    else
    {
        m_SongListFrame->setGeometry(width()-m_SongListFrame->width(),height()-m_SongListFrame->height()-m_BottomWidget->height(),580,470);
        m_SongListFrame->show();
        m_SongListFrame->raise();
    }
}

//if silence->restore; if not->restore
void MainWidget::slot_silence()
{
    if(0 == player->volume())
    {
        player->setVolume(curVolume);
        m_BottomWidget->volumeBtn->setToolTip(QString::number(curVolume,10));
        m_BottomWidget->volumeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/volume.png)}");
        m_MiniWidget->m_volBtn->setStyleSheet("QPushButton{background:transparent;\
                                border-image:url(:/images/mini/vol.png);}");
    }
    else
    {
        curVolume = player->volume();
        player->setVolume(0);
        m_BottomWidget->volumeBtn->setToolTip(" 静音 ");
        m_BottomWidget->volumeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/volumeSilence.png)}");
        m_MiniWidget->m_volBtn->setStyleSheet("QPushButton{background:transparent;\
                                border-image:url(:/images/mini/silence.png);}");
    }
}

//double click to play local music
void MainWidget::slot_PlayLocalMusic(QTableWidgetItem* tableItem)
{
    QPixmap default_photo = QPixmap(":/images/SongInfo/cdCover.png");
    default_photo = default_photo.scaled(60,60,Qt::KeepAspectRatio);
    m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(default_photo);
    default_photo = default_photo.scaled(42,42,Qt::KeepAspectRatio);
    m_MiniWidget->m_photoLabel->setPixmap(default_photo);
    m_turntableWidget->pix_cd = default_photo; m_turntableWidget->update();

    m_SongListFrame->m_PlayingList->clear();
    for(int i=0; i<m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->rowCount(); ++i)
    {
        QListWidgetItem *item = new QListWidgetItem;
        m_SongListFrame->m_PlayingList->addItem(item);
        PlayListItemStyle *itemStyle = new PlayListItemStyle(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(i,1)->text(),
                                                             m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(i,2)->text(),
                                                             m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(i,4)->text());
        m_SongListFrame->m_PlayingList->setItemWidget(item,itemStyle);
        item->setSizeHint(QSize(itemStyle->rect().width(),itemStyle->rect().height()));
    }
    m_SongListFrame->getCountLabel()->setText(QString("总%1首").arg(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->rowCount()));

    curPlaySong = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(tableItem->row(),1)->text();
    curPlaySinger = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(tableItem->row(),2)->text();


    QString show_songname;
    if(curPlaySong.length() > 11)
    {
        show_songname = curPlaySong.mid(0,10);
        show_songname.append("...");
    }

    m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySinger);

    if(curPlaySong.length() > 11)
        m_MiniWidget->m_songNameLab->setText(show_songname);
    else
        m_MiniWidget->m_songNameLab->setText(curPlaySong);
    m_MiniWidget->m_singleLab->setText(curPlaySinger);

    if(curPlaySong.length() > 11)
        m_TrayMenu->curPlaySongAction->setText(show_songname+" - "+curPlaySinger);
    else
        m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySinger);

    m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySinger);

    m_TrayMenu->pauseAction->setText("暂停");
    m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));

    m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png)}");

    player->setPlaylist(m_MiddleWidget->m_Stack->localPlayList);
    m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(tableItem->row());
    player->play();
    isMediaPlay = true;
    m_BottomWidget->playBtn->setToolTip(" 暂停 ");

    m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/pause.png"));
    m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
    m_BottomWidget->endTimeLabel->setText(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(tableItem->row(),4)->text());

    m_turntableWidget->record_timer->start();
    m_turntableWidget->stylus_in_timer->start();
    m_turntableWidget->music_titelLabel->setText(curPlaySong);
    m_turntableWidget->music_erLabel->setText(curPlaySinger);
    m_turntableWidget->special_Label->setText("本地资源");


    TagLib::MPEG::File fx(m_MiddleWidget->m_Stack->localPlayList->currentMedia().canonicalUrl().path().toStdString().c_str());
    TagLib::ID3v2::FrameList frameList = fx.ID3v2Tag()->frameListMap()["APIC"];
    if (!frameList.isEmpty())
    {
        TagLib::ID3v2::AttachedPictureFrame *picFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (frameList.front());
        QPixmap photo;
        photo.loadFromData(reinterpret_cast<const uchar*>(picFrame->picture().data()), picFrame->picture().size());
        photo = photo.scaled(60,60,Qt::KeepAspectRatio);
        m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(photo);
        photo = photo.scaled(42,42,Qt::KeepAspectRatio);
        m_MiniWidget->m_photoLabel->setPixmap(photo);
        photo.loadFromData(reinterpret_cast<const uchar*>(picFrame->picture().data()), picFrame->picture().size());
        m_turntableWidget->pix_cd = photo; m_turntableWidget->update();
    }

}

//next music
void MainWidget::slot_playNext()
{
    QPixmap default_photo = QPixmap(":/images/SongInfo/cdCover.png");
    default_photo = default_photo.scaled(60,60,Qt::KeepAspectRatio);
    m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(default_photo);
    default_photo = default_photo.scaled(42,42,Qt::KeepAspectRatio);
    m_MiniWidget->m_photoLabel->setPixmap(default_photo);
    m_turntableWidget->pix_cd = default_photo; m_turntableWidget->update();

    if(m_SongListFrame->m_PlayingList->count() != 0)
    {
        int currentIndex = m_MiddleWidget->m_Stack->localPlayList->currentIndex();
        if(++currentIndex == m_MiddleWidget->m_Stack->localPlayList->mediaCount())
            currentIndex = 0;

        curPlaySong = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,1)->text();
        curPlaySinger = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,2)->text();

        QString show_songname;
        if(curPlaySong.length() > 11)
        {
            show_songname = curPlaySong.mid(0,10);
            show_songname.append("...");
        }
        m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySinger);

        if(curPlaySong.length() > 11)
            m_MiniWidget->m_songNameLab->setText(show_songname);
        else
            m_MiniWidget->m_songNameLab->setText(curPlaySong);
        m_MiniWidget->m_singleLab->setText(curPlaySinger);

        if(curPlaySong.length() > 11)
            m_TrayMenu->curPlaySongAction->setText(show_songname+" - "+curPlaySinger);
        else
            m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySinger);

        m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySinger);

        m_TrayMenu->pauseAction->setText("暂停");
        m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));

        m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png)}");

        m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(currentIndex);
        player->play();
        isMediaPlay = true;
        m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/pause.png"));
        m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
        m_BottomWidget->endTimeLabel->setText(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,4)->text());

        m_turntableWidget->record_timer->start();
        m_turntableWidget->stylus_in_timer->start();
        m_turntableWidget->music_titelLabel->setText(curPlaySong);
        m_turntableWidget->music_erLabel->setText(curPlaySinger);
        m_turntableWidget->special_Label->setText("本地资源");


        TagLib::MPEG::File fx(m_MiddleWidget->m_Stack->localPlayList->currentMedia().canonicalUrl().path().toStdString().c_str());
        TagLib::ID3v2::FrameList frameList = fx.ID3v2Tag()->frameListMap()["APIC"];
        if (!frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *picFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (frameList.front());
            QPixmap photo;
            photo.loadFromData(reinterpret_cast<const uchar*>(picFrame->picture().data()), picFrame->picture().size());
            photo = photo.scaled(60,60,Qt::KeepAspectRatio);
            m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(photo);
            photo = photo.scaled(42,42,Qt::KeepAspectRatio);
            m_MiniWidget->m_photoLabel->setPixmap(photo);
            photo.loadFromData(reinterpret_cast<const uchar*>(picFrame->picture().data()), picFrame->picture().size());
            m_turntableWidget->pix_cd = photo; m_turntableWidget->update();
        }
    }
}

//pre music
void MainWidget::slot_playPre()
{
    QPixmap default_photo = QPixmap(":/images/SongInfo/cdCover.png");
    default_photo = default_photo.scaled(60,60,Qt::KeepAspectRatio);
    m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(default_photo);
    default_photo = default_photo.scaled(42,42,Qt::KeepAspectRatio);
    m_MiniWidget->m_photoLabel->setPixmap(default_photo);
    m_turntableWidget->pix_cd = default_photo; m_turntableWidget->update();

    if(m_SongListFrame->m_PlayingList->count() != 0)
    {
        int currentIndex = m_MiddleWidget->m_Stack->localPlayList->currentIndex();
        if(currentIndex == 0)
            currentIndex = m_MiddleWidget->m_Stack->localPlayList->mediaCount()-1;
        else
            --currentIndex;
        curPlaySong = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,1)->text();
        curPlaySinger = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,2)->text();

        QString show_songname;
        if(curPlaySong.length() > 11)
        {
            show_songname = curPlaySong.mid(0,10);
            show_songname.append("...");
        }
        m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySinger);

        if(curPlaySong.length() > 11)
            m_MiniWidget->m_songNameLab->setText(show_songname);
        else
            m_MiniWidget->m_songNameLab->setText(curPlaySong);
        m_MiniWidget->m_singleLab->setText(curPlaySinger);

        if(curPlaySong.length() > 11)
            m_TrayMenu->curPlaySongAction->setText(show_songname+" - "+curPlaySinger);
        else
            m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySinger);

        m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySinger);

        m_TrayMenu->pauseAction->setText("暂停");
        m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));

        m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png)}");

        m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(currentIndex);
        player->play();
        isMediaPlay = true;
        m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/pause.png"));
        m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
        m_BottomWidget->endTimeLabel->setText(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,4)->text());

        m_turntableWidget->record_timer->start();
        m_turntableWidget->stylus_in_timer->start();
        m_turntableWidget->music_titelLabel->setText(curPlaySong);
        m_turntableWidget->music_erLabel->setText(curPlaySinger);
        m_turntableWidget->special_Label->setText("本地资源");


        TagLib::MPEG::File fx(m_MiddleWidget->m_Stack->localPlayList->currentMedia().canonicalUrl().path().toStdString().c_str());
        TagLib::ID3v2::FrameList frameList = fx.ID3v2Tag()->frameListMap()["APIC"];
        if (!frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *picFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (frameList.front());
            QPixmap photo;
            photo.loadFromData(reinterpret_cast<const uchar*>(picFrame->picture().data()), picFrame->picture().size());
            photo = photo.scaled(60,60,Qt::KeepAspectRatio);
            m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(photo);
            photo = photo.scaled(42,42,Qt::KeepAspectRatio);
            m_MiniWidget->m_photoLabel->setPixmap(photo);
            m_turntableWidget->pix_cd = photo; m_turntableWidget->update();
        }
    }
}

void MainWidget::slot_updatePosition(qint64 position)
{
    m_BottomWidget->playTimeSlider->setValue(static_cast<int>(position));
    QTime duration(0, static_cast<int>(position) / 60000, static_cast<int>((position % 60000) / 1000.0));
    m_BottomWidget->startTimeLabel->setText(duration.toString("mm:ss"));
}

void MainWidget::slot_updateDuration(qint64 duration)
{
    m_BottomWidget->playTimeSlider->setRange(0,static_cast<int>(duration));
    m_BottomWidget->playTimeSlider->setEnabled(duration>0);
    m_BottomWidget->playTimeSlider->setPageStep(static_cast<int>(duration)/10);
}

void MainWidget::slot_setPosition(int position)
{
    if (qAbs(player->position() - position) > 99)
        player->setPosition(position);
}

//when normally end a music
void MainWidget::slot_updateSongInfo(QMediaContent c)
{
    Q_UNUSED(c);

    int currentIndex = m_MiddleWidget->m_Stack->localPlayList->currentIndex();
    if( currentIndex != -1 ) //for when not error; just for Seq and final music
    {
        curPlaySong = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,1)->text();
        curPlaySinger = m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,2)->text();

        QString show_songname;
        if(curPlaySong.length() > 11)
        {
            show_songname = curPlaySong.mid(0,10);
            show_songname.append("...");
        }
        m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySinger);

        if(curPlaySong.length() > 11)
            m_MiniWidget->m_songNameLab->setText(show_songname);
        else
            m_MiniWidget->m_songNameLab->setText(curPlaySong);
        m_MiniWidget->m_singleLab->setText(curPlaySinger);

        if(curPlaySong.length() > 11)
            m_TrayMenu->curPlaySongAction->setText(show_songname+" - "+curPlaySinger);
        else
            m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySinger);

        m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySinger);

        m_TrayMenu->pauseAction->setText("暂停");
        m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));

        m_MiniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png)}");

        m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(currentIndex);
        player->play();
        isMediaPlay = true;
        m_BottomWidget->playBtn->setIcon(QIcon(":/images/BottomPlay/pause.png"));
        m_BottomWidget->playBtn->setIconSize(m_BottomWidget->lastBtn->size());
        m_BottomWidget->endTimeLabel->setText(m_MiddleWidget->m_Stack->localMusic_BaseStack->m_StackFrame1TableWidget->item(currentIndex,4)->text());


        TagLib::MPEG::File fx(m_MiddleWidget->m_Stack->localPlayList->currentMedia().canonicalUrl().path().toStdString().c_str());
        TagLib::ID3v2::FrameList frameList = fx.ID3v2Tag()->frameListMap()["APIC"];
        if (!frameList.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *picFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (frameList.front());
            QPixmap photo;
            photo.loadFromData(reinterpret_cast<const uchar*>(picFrame->picture().data()), picFrame->picture().size());
            photo = photo.scaled(60,60,Qt::KeepAspectRatio);
            m_MiddleWidget->m_PlaySongInfoWidget->cdLabel->setPixmap(photo);
            photo = photo.scaled(42,42,Qt::KeepAspectRatio);
            m_MiniWidget->m_photoLabel->setPixmap(photo);
        }
    }
}

void MainWidget::closeEvent(QCloseEvent *event)
{
  Q_UNUSED(event);
  writeSettings();
}
