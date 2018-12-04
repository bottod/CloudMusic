#include "MiddleWidget.h"

MiddleWidget::MiddleWidget(QWidget *parent) : QWidget(parent)
{
    m_hmainLayout = new QHBoxLayout(this);
    m_vListLayout = new QVBoxLayout;

    m_List = new MiddleWidgetLeftList(this);
    m_PlaySongInfoWidget = new PlaySongInfoWidget(this);

    m_vListLayout->addWidget(m_List);
    m_vListLayout->addWidget(m_PlaySongInfoWidget);
    m_vListLayout->setSpacing(0);

    m_Stack = new MiddleWidgetRightStack(this);
    for(int i=0; i<m_List->m_btnVec.size(); ++i)
        connect(m_List->m_btnVec.at(i),&QPushButton::clicked,m_Stack,[=](){m_Stack->setCurrentIndex(i);});

    m_hmainLayout->addLayout(m_vListLayout);
    m_hmainLayout->addWidget(m_Stack);
    m_hmainLayout->setMargin(0);
    m_hmainLayout->setSpacing(0);


    m_SelectDirFrame = new SelectDirFrame;

    QSettings settings;
    int size = settings.beginReadArray("music_path");
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        MusicPath path;
        path.path = settings.value("path").toString();
        path.ischecked = settings.value("ischecked").toBool();

        QListWidgetItem *item = new QListWidgetItem;
        QCheckBox *checkBox = new QCheckBox;
        checkBox->setText(path.path);
        checkBox->setToolTip(path.path);
        m_SelectDirFrame->checkList->addItem(item);
        m_SelectDirFrame->checkList->setItemWidget(item,checkBox);
        checkBox->setChecked(path.ischecked);
    }
    settings.endArray();
    m_SelectDirFrame->getCheckedState();
    m_Stack->SongDirPath = m_SelectDirFrame->DirList;
    m_Stack->slot_widget4MatchSong();


    connect(m_Stack->localMusic_BaseStack->m_selectBtn,&QPushButton::clicked,this,[=](){m_SelectDirFrame->show();});
    connect(m_SelectDirFrame->m_ackBtn,&QPushButton::clicked,this,&MiddleWidget::slot_ackDir);


}

void MiddleWidget::slot_ackDir()
{

    m_SelectDirFrame->getCheckedState();
    //when clicked ok just start once matching; not wait
    m_Stack->SongDirPath = m_SelectDirFrame->DirList;
    m_Stack->slot_widget4MatchSong();
    m_SelectDirFrame->close();
}
