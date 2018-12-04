#ifndef SONGLISTFRAME_H
#define SONGLISTFRAME_H

#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QListWidget>
#include <QSignalMapper>

class SongListFrame : public QFrame
{
    Q_OBJECT
public:
    explicit SongListFrame(QWidget *parent = nullptr);

    void focusOutEvent(QFocusEvent *);

    QLabel* getCountLabel(){return m_CountLabel;}

private slots:
    void slot_ShowHideBtn();

private:
    void initFrame();
    void initPlayList();
    void initConnect();

    QStackedWidget *m_StackWin;
    QFrame *m_BtnFrame, *m_StatusFrmae;
    QPushButton *m_PlayingBtn, *m_PlaysBtn, *m_CollectBtn, *m_EmptyBtn, *m_CloseBtn;
    QLabel *m_CountLabel, *m_LineLabel;
    QVBoxLayout *m_vMainLayout;

    QButtonGroup *mutexBtnGroup;
    QSignalMapper *m_signalMapper;

public:
    QListWidget *m_PlayingList, *m_PlaysList;
};

#endif // SONGLISTFRAME_H
