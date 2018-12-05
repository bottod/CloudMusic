#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSystemTrayIcon>
#include <QTableWidgetItem>
#include <QPropertyAnimation>
#include <QSettings>
#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>

#include "FramelessWidget.h"
#include "TitleBar.h"
#include "miniWidget.h"
#include "TrayIconMenu.h"
#include "BottomWidget.h"
#include "MiddleWidget.h"
#include "SongListFrame.h"
#include "PlayListItemStyle.h"
#include "SkinWidget.h"
#include "TurntableWidget.h"

#include <mpegfile.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>

class MainWidget : public FramelessWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

signals:
    void sig_searchName(QString search_name);

public:
    SkinWidget *m_skinWidget;

    QWidget *m_turnTableLayoutWidget;
    TurntableWidget *m_turntableWidget;

public slots:
    void slot_showMainWidget();
    void slot_showMiniWidget();
    void slot_showMaximized();
    void slot_showSkinWidget();
    void slot_showTurnTableWidget();
    void slot_hideTurnTableWidget();
    void slot_onActivated(QSystemTrayIcon::ActivationReason);
    void slot_quitOrhide();
    void slot_playPause();
    void slot_playModeChange();
    void slot_changeSongListPos(int newWidth, int newHeight);
    void slot_showSongListWidget();
    void slot_silence();
    void slot_PlayLocalMusic(QTableWidgetItem* tableItem);
    void slot_playNext();
    void slot_playPre();
    void slot_updatePosition(qint64 position);
    void slot_updateDuration(qint64 duration);
    void slot_setPosition(int position);
    void slot_updateSongInfo(QMediaContent c);

private:
    QVBoxLayout *mainLayout;
    TitleBar    *m_TitleBar;
    MiddleWidget *m_MiddleWidget;
    BottomWidget *m_BottomWidget;
    miniWidget  *m_MiniWidget;
    QSystemTrayIcon *m_SystemTray;
    TrayIconMenu *m_TrayMenu;
    void initSystemTray();

    bool isMediaPlay = false; //default not play media

    //in settings; default not this value all in settings
    bool isMaximun = false;

    bool isFirstOpen = true; //open app without default-quit or hide-config ; it must be false so that dialog not show
    bool isQuitHide = true; //quit:true or hide:false
    int playMode = 0; // 0:Sequential | 1:Loop | 2:CurrentItemInLoop | 3:Random

    int widget_color = -1;//-1 default;

    //write conf in ~/.config
    void writeSettings();
    void readSettings();

    SongListFrame *m_SongListFrame;
    int m_SongListFrameX, m_SongListFrameY;

    QMediaPlayer *player;
    int curVolume = 0; //value:0-100; define in BottomWidget; real value in conf
    QString curPlaySong;
    QString curPlaySinger;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWIDGET_H
