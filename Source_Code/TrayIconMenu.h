#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QMenu>
#include <QFile>

class TrayIconMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TrayIconMenu(QWidget *parent = nullptr);

signals:


private:
    void initAction();

public:
    QAction *curPlaySongAction;
    QAction *pauseAction;
    QAction *lastAction;
    QAction *nextAction;

    QMenu *playModeMenu;
    QAction *playMode_Sequential_Action;
    QAction *playMode_Loop_Action;
    QAction *playMode_CurrentItemInLoop_Action;
    QAction *playMode_Random_Action;

    QMenu *windowStyleMenu;
    QAction *complete_Window_Action;
    QAction *mini_Window_Action;

    QAction *openLyricAction;
    QAction *lockLyricAction;
    QAction *setAction;
    QAction *quitAction;
};

#endif // TRAYICONMENU_H
