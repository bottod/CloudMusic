#include "PlayListItemStyle.h"
#include <QtDebug>

PlayListItemStyle::PlayListItemStyle(QString songName, QString singerName, QString songTime, QWidget *parent):QFrame(parent)
{
    setFixedHeight(35);

    m_playStatus = new QLabel(this);
    m_playStatus->setGeometry(13,15,6,10);
    m_playStatus->setToolTip(m_playStatus->text());
    m_playStatus->setStyleSheet("QLabel{background:transparent;border-image:url(:/images/SongList/playLabel.png)}");

    QString show_songname = "";
    if(songName.length() > 15)
    {
        show_songname = songName.mid(0,14);
        show_songname.append("...");
        m_songName = new QLabel(show_songname,this);
        m_songName->adjustSize();
        m_songName->setGeometry(31,9,m_songName->width(),18);
        m_songName->setToolTip(songName);
        m_songName->setStyleSheet("QLabel{border:none}");
    }
    else
    {
        m_songName = new QLabel(songName,this);
        m_songName->adjustSize();
        m_songName->setGeometry(31,9,m_songName->width(),18);
        m_songName->setToolTip(m_songName->text());
        m_songName->setStyleSheet("QLabel{border:none}");
    }

    m_singerBtn = new QPushButton(singerName,this);
    m_singerBtn->adjustSize();
    m_singerBtn->setGeometry(373,9,m_singerBtn->width(),18);
    m_singerBtn->setCursor(Qt::PointingHandCursor);
    m_singerBtn->setToolTip(m_singerBtn->text());
    m_singerBtn->setStyleSheet("QPushButton{background:transparent;color:#888888;border:none}");

    m_sourceBtn = new QPushButton(this);
    m_sourceBtn->setGeometry(482,15,13,13);
    m_sourceBtn->setCursor(Qt::PointingHandCursor);
    m_sourceBtn->setToolTip("来源:");
    m_sourceBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/SongList/source.png)}");

    m_songTime = new QLabel(songTime,this);
    m_songTime->adjustSize();
    m_songTime->setGeometry(514,9,m_songTime->width(),m_songTime->height());
    m_songTime->setStyleSheet("QLabel{border:none}");
}
