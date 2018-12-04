#ifndef MINIWIDGET_H
#define MINIWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

const QString miniMainColor = "QFrame{background:rgb(102,183,255)}";

#pragma pack(push)
#pragma pack(1)

class miniWidget : public QFrame
{
    Q_OBJECT
public:
    explicit miniWidget(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    QFrame *m_mainFrame;

    QLabel *m_photoLabel;
    QPushButton *m_loveBtn;
    QPushButton *m_volBtn;
    QPushButton *m_listBtn;

    QPushButton *m_closeBtn;
    QPushButton *m_recoveryWinBtn;

    QPushButton *m_preBtn;
    QPushButton *m_playStateBtn;
    QPushButton *m_nextBtn;

    QLabel *m_songNameLab;
    QLabel *m_singleLab;

private:
    void init_miniWidget();
    bool m_mouseState;

    QPoint  m_WindowPos;
    QPoint m_MousePos;

    QHBoxLayout *m_hMainLayout;
    QHBoxLayout *m_hPlayLayout;

    QFrame *m_palyFrame;

    QVBoxLayout *m_vMainLayout;
    QVBoxLayout *m_vInfoLayout;
    QVBoxLayout *m_vSysLayout;
};

#pragma pack(pop)

#endif // MINIWIDGET_H
