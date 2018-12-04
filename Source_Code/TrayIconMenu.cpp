#include "TrayIconMenu.h"

TrayIconMenu::TrayIconMenu(QWidget *parent) : QMenu(parent)
{
    setFixedWidth(212);

    initAction();
}

void TrayIconMenu::initAction()
{
    setStyleSheet("QMenu{background:#fafafc;}"
                  "QMenu::item{height: 28px;padding: 0px 20px 0px 40px;font-size : 12px}"
                  "QMenu::item:hover{background:#ededef}"
                  "QMenu::icon{position: absolute;left: 12px;}"
                  "QMenu::separator{height:1px;background: #ededef;margin:5px 0px 5px 0px;}");

    curPlaySongAction = new QAction(QIcon(":/images/TrayIcon/curPlaySong.png"), "未知 - 未知", this);
    pauseAction = new QAction(QIcon(":/images/TrayIcon/play.png"), "播放", this);
    lastAction = new QAction(QIcon(":/images/TrayIcon/last.png"), "上一首", this);
    nextAction = new QAction(QIcon(":/images/TrayIcon/next.png"), "下一首", this);

    playModeMenu = new QMenu("顺序播放",this);
    playMode_Sequential_Action = new QAction(QIcon(":/images/BottomPlay/Sequential.png"), "顺序播放", playModeMenu);
    playMode_Loop_Action = new QAction(QIcon(":/images/BottomPlay/Loop.png"), "列表循环", playModeMenu);
    playMode_CurrentItemInLoop_Action = new QAction(QIcon(":/images/BottomPlay/CurrentItemInLoop.png"), "单曲循环", playModeMenu);
    playMode_Random_Action = new QAction(QIcon(":/images/BottomPlay/Random.png"), "随机播放", playModeMenu);
    playModeMenu->addAction(playMode_Sequential_Action);
    playModeMenu->addAction(playMode_Loop_Action);
    playModeMenu->addAction(playMode_CurrentItemInLoop_Action);
    playModeMenu->addAction(playMode_Random_Action);

    windowStyleMenu = new QMenu("完整模式",this);
    complete_Window_Action = new QAction("完整模式",windowStyleMenu);
    mini_Window_Action = new QAction(QIcon(":/images/TrayIcon/mini.png"), "mini模式", windowStyleMenu);
    windowStyleMenu->addAction(complete_Window_Action);
    windowStyleMenu->addAction(mini_Window_Action);

    openLyricAction = new QAction(QIcon(":/images/TrayIcon/openLyric.png"), "打开桌面歌词", this);
    lockLyricAction = new QAction(QIcon(":/images/TrayIcon/lockLyric.png"), "锁定桌面歌词", this);
    setAction = new QAction(QIcon(":/images/TrayIcon/set.png"), "设置", this);
    quitAction = new QAction(QIcon(":/images/TrayIcon/quit.png"), "退出", this);

    addAction(curPlaySongAction);
    addAction(pauseAction);
    addAction(lastAction);
    addAction(nextAction);
    addSeparator();
    addMenu(playModeMenu);
    addMenu(windowStyleMenu);
    addAction(openLyricAction);
    addAction(lockLyricAction);
    addSeparator();
    addAction(setAction);
    addSeparator();
    addAction(quitAction);
}
