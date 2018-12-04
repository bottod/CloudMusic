#include "MiddleWidgetRightStack.h"


MiddleWidgetRightStack::MiddleWidgetRightStack(QWidget *parent) : QStackedWidget(parent)
{
    setStyleSheet("QStackedWidget{background:rgb(250,250,250)}");

    findMusic_BaseStack = new ListWidgetFindMusic(this);


    localMusic_BaseStack = new ListWidgetLocalMusic(this);
    connect(localMusic_BaseStack->m_matchMusicBtn, &QPushButton::clicked, this, &MiddleWidgetRightStack::slot_widget4MatchSong);

    addWidget(findMusic_BaseStack);
    addWidget(new QLabel("window 1",this));
    addWidget(new QLabel("window 2",this));
    addWidget(new QLabel("window 3",this));
    addWidget(localMusic_BaseStack);
    addWidget(new QLabel("window 5",this));
    addWidget(new QLabel("window 6",this));
    addWidget(new QLabel("window 7",this));
}

MiddleWidgetRightStack::~MiddleWidgetRightStack()
{
}


void MiddleWidgetRightStack::setTableItem(int rownum, QString title, QString singal, QString cd, QString time, QString size)
{
    localMusic_BaseStack->m_StackFrame1TableWidget->insertRow(rownum);
    QString num = QString("%1").arg(rownum+1, 2, 10, QChar('0'));

    QTableWidgetItem *item0 = new QTableWidgetItem(num);
    QTableWidgetItem *item1 = new QTableWidgetItem(title);
    QTableWidgetItem *item2 = new QTableWidgetItem(singal);
    QTableWidgetItem *item3 = new QTableWidgetItem(cd);
    QTableWidgetItem *item4 = new QTableWidgetItem(time);
    QTableWidgetItem *item5 = new QTableWidgetItem(size);

    localMusic_BaseStack->m_StackFrame1TableWidget->setItem(rownum,0,item0);
    localMusic_BaseStack->m_StackFrame1TableWidget->item(rownum,0)->setTextAlignment(Qt::AlignCenter|Qt::AlignRight);
    localMusic_BaseStack->m_StackFrame1TableWidget->setItem(rownum,1,item1);
    localMusic_BaseStack->m_StackFrame1TableWidget->item(rownum,1)->setTextColor(QColor(0,0,0));
    localMusic_BaseStack->m_StackFrame1TableWidget->setItem(rownum,2,item2);
    localMusic_BaseStack->m_StackFrame1TableWidget->setItem(rownum,3,item3);
    localMusic_BaseStack->m_StackFrame1TableWidget->setItem(rownum,4,item4);
    localMusic_BaseStack->m_StackFrame1TableWidget->setItem(rownum,5,item5);
}

void MiddleWidgetRightStack::slot_widget4MatchSong()
{
    //every time match clean content first
    localPlayList = new QMediaPlaylist(this);
    localMusic_BaseStack->m_StackFrame1TableWidget->clearContents();
    localMusic_BaseStack->m_StackFrame1TableWidget->setRowCount(0);
    rowcount = 0;
    MD5List.clear();

    int countSum = 0;
    //SongDirPath changed in "MiddleWidget::slot_ackDir"
    for(int i=0; i<SongDirPath.count(); ++i)
    {
        matchDir.setPath(SongDirPath.at(i));
        matchDir.setNameFilters(QStringList("*.mp3"));//Filter file with ".mp3"
        matchMp3Files = matchDir.entryList();//List all eligible documents
        countSum = matchMp3Files.count();
        for(int j=0; j<countSum; j++)
        {
            mp3Name = SongDirPath.at(i) + '/' + matchMp3Files.at(j);

            //compare file md5
            QFile file(mp3Name);
            file.open(QIODevice::ReadOnly);
            MD5Str = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5).toHex().constData();
            file.close();

            if(MD5List.contains(MD5Str))
                continue;
            MD5List.append(MD5Str);

            //add music to play list
            localPlayList->addMedia(QUrl::fromLocalFile(mp3Name));

            //mp3 size
            fileInfo.setFile(mp3Name);
            qint64 fileSize= fileInfo.size();
            if(fileSize/1024)
            {
                if(fileSize/1024/1024)
                {
                    if(fileSize/1024/1024/1024)
                    {
                        mp3Size = QString::number(fileSize/1024/1024/1024,10)+"GB";
                    }
                    else
                       mp3Size = QString::number(fileSize/1024/1024,10)+"MB";
                }
                else
                    mp3Size = QString::number(fileSize/1024,10)+"KB";
            }
            else
                mp3Size = QString::number(fileSize,10)+"B";

            bytes = mp3Name.toLocal8Bit();

            TagLib::FileRef f(bytes.data());

            if(f.isNull())
            {
                //can't read this music;
                continue;
            }

            TagLib::PropertyMap tags = f.file()->properties();

            //ALBUM专辑 ARTIST艺术家 TITLE标题
            titleStr = tags["TITLE"].toString().toCString(true);
            if(titleStr.isEmpty())
                titleStr = fileInfo.baseName();

            artistStr = tags["ARTIST"].toString().toCString(true);
            if(artistStr.isEmpty())
                artistStr="未知";

            albumStr = tags["ALBUM"].toString().toCString(true);
            if(albumStr.isEmpty())
                albumStr="未知";

            TagLib::AudioProperties *properties = f.audioProperties();

            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;
            timeStr = QString::number(minutes)+":"+QString("%1").arg(seconds, 2, 10, QChar('0'));

            //get pre for insert
            rowcount = localMusic_BaseStack->m_StackFrame1TableWidget->rowCount();

            setTableItem(rowcount, titleStr, artistStr, albumStr, timeStr, mp3Size);
            //getlast insert
            rowcount = localMusic_BaseStack->m_StackFrame1TableWidget->rowCount();
        }
    }
    //update how many songs
    localMusic_BaseStack->m_CountLabel->setText(QString("%1首音乐,").arg(rowcount));
}
