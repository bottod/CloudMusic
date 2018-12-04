#ifndef LISTWIDGETFINDMUSIC_H
#define LISTWIDGETFINDMUSIC_H

#include <QWidget>
#include <QPainter>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QFrame>

#include "AnimationWidget.h"

class ListWidgetFindMusic : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidgetFindMusic(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

public:
    QStackedWidget *findMusicStack;
    QPushButton *recommendBtn, *songListBtn, *radioBtn, *rankBtn, *singleBtn, *newMusicBtn;
    QButtonGroup *mutexBtnGroupFindMusic;
    QVector<QPushButton*> m_btnVec_FindMusic;
    QHBoxLayout *h_btnBarLayout;
    QVBoxLayout *v_mainLayout;

    QWidget *personal_widget;
    AnimationWidget *m_animationFrame1;
    AnimationWidget *m_animationFrame2;

private:
    void init();
};

#endif // LISTWIDGETFINDMUSIC_H
