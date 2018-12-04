#ifndef PLAYLISTITEMSTYLE_H
#define PLAYLISTITEMSTYLE_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>

class PlayListItemStyle : public QFrame
{
    Q_OBJECT
public:
    PlayListItemStyle(QString songName, QString singerName, QString songTime, QWidget *parent = nullptr);

    QLabel *m_playStatus, *m_songName, *m_songTime;
    QPushButton *m_singerBtn, *m_sourceBtn;
};

#endif // PLAYLISTITEMSTYLE_H
