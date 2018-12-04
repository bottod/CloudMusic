#ifndef MIDDLEWIDGETRIGHTSTACK_H
#define MIDDLEWIDGETRIGHTSTACK_H

#include <QStackedWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMovie>
//#include <QThread>
#include <QFile>
#include <QCryptographicHash>

//TagLib
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/toolkit/tpropertymap.h>

#include "ListWidgetFindMusic.h"
#include "ListWidgetLocalMusic.h"


class MiddleWidgetRightStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MiddleWidgetRightStack(QWidget *parent = nullptr);
    ~MiddleWidgetRightStack();

public slots:
    void slot_widget4MatchSong();

private:
    void setTableItem(int rownum, QString title, QString singal, QString cd, QString time, QString size);


public:
    ListWidgetFindMusic *findMusic_BaseStack;
    ListWidgetLocalMusic *localMusic_BaseStack;

    int rowcount;
    QStringList SongDirPath;
    QDir matchDir;
    QStringList matchMp3Files;
    QString mp3Name;

    QFileInfo fileInfo;
    QByteArray bytes;
    QString titleStr;
    QString artistStr;
    QString albumStr;
    QString timeStr;
    QString mp3Size;

    QString MD5Str;
    QStringList MD5List;

    //local music list
    QMediaPlaylist *localPlayList;
};

#endif // MIDDLEWIDGETRIGHTSTACK_H
