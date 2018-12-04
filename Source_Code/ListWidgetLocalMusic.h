#ifndef LISTWIDGETLOCALMUSIC_H
#define LISTWIDGETLOCALMUSIC_H

#include <QWidget>
#include <QMediaPlaylist>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QLineEdit>
#include <QTableWidget>
#include <QScrollBar>
#include <QHeaderView>

class ListWidgetLocalMusic : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidgetLocalMusic(QWidget *parent = nullptr);

public:
    QVBoxLayout *m_MainLayout;

    //main title
    QMediaPlaylist *localPlayList;
    QFrame *titleFrame;
    QHBoxLayout *hTitleLayout;
    QLabel *m_localLabel;
    QLabel *m_CountLabel;
    QPushButton *m_selectBtn;
    QPushButton *m_listBtn;
    QPushButton *m_singalBtn;
    QPushButton *m_cdBtn;
    QPushButton *m_dirBtn;

    QButtonGroup *mutexBtnGroupLocalMusic;
    QVector<QPushButton*> m_btnVec_LocalMusic;
    QStackedWidget *localMusicStack;


    //stack1
    QFrame *stackFrame1;
    QFrame *stackFrame1Title;
    QHBoxLayout *hStackFrame1TitleLayout;
    QPushButton *m_playAllBtn;
    QPushButton *m_addBtn;
    QPushButton *m_matchMusicBtn;
    QLineEdit *m_searchEdit;
    QLabel *m_searchLabel;
    QTableWidget *m_StackFrame1TableWidget;

private:
    void initTitle();
    void initStack();
};

#endif // LISTWIDGETLOCALMUSIC_H
