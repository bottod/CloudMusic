#ifndef MIDDLEWIDGETLEFTLIST_H
#define MIDDLEWIDGETLEFTLIST_H

#include <QFrame>
#include <QToolButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>

class MiddleWidgetLeftList : public QFrame
{
    Q_OBJECT
public:
    explicit MiddleWidgetLeftList(QWidget *parent = nullptr);

    QPushButton *findMusicBtn, *privateFMBtn, *mvBtn, *friendBtn;
    QPushButton *localMusicBtn, *downManageBtn, *myMusicBoxBtn, *mySingerBtn;
    QVector<QPushButton*> m_btnVec;
private:
    void initTopWidget();
    void initBtnVec();

    QLabel *recommendLabel, *myMusicLabel;

    QButtonGroup *mutexBtnGroup;

};

#endif // MIDDLEWIDGETLEFTLIST_H
