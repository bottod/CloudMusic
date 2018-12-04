#include "SelectDirFrame.h"
#include <QFileDialog>
#include <QScrollBar>

#include <QDebug>

SelectDirFrame::SelectDirFrame(QWidget *parent) : FramelessWidget(parent)
{
    setStyleSheet("QFrame{border-color:rgb(225,225,225);border-width: 1;border-style: solid}");

    setAttribute(Qt::WA_ShowModal,true);

    setFixedSize(300,350);

    //title
    m_Title = new QFrame(this);
    m_Title->setFixedHeight(50);
    m_Title->setStyleSheet("QFrame{background:#ffffff}");
    m_Title->setCursor(Qt::SizeAllCursor);
    title_Layout = new QHBoxLayout(m_Title);
    seleLocalDir = new QLabel("选择本地音乐文件夹",m_Title);
    seleLocalDir->setStyleSheet("QLabel{font:bold 15px;color:#666666;border:none}");
    seleLocalDir->setFixedSize(145,20);

    m_closeBtn = new QPushButton(m_Title);
    m_closeBtn->setFixedSize(10,9);
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/close.png)}");

    title_Layout->setMargin(0);
    title_Layout->setSpacing(0);
    title_Layout->addSpacing(20);
    title_Layout->addWidget(seleLocalDir);
    title_Layout->addSpacing(100);
    title_Layout->addWidget(m_closeBtn);


    //content
    m_Content = new QFrame(this);
    m_Content->setFixedHeight(240);
    m_Content->setStyleSheet("QFrame{background:#ffffff}");
    content_Layout = new QVBoxLayout(m_Content);
    description = new QLabel("将自动扫描您勾选的目录，文件增删实时同步。");
    description->adjustSize();
    description->setStyleSheet("QLabel{border:none;font:13px}");

    checkList = new QListWidget(this);
    checkList->setFixedSize(280,180);
    checkList->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    checkList->setStyleSheet("QListWidget{border:none}"
                             "QListWidget::Item:hover{background:#ffffff}"
                             "QListWidget::item:selected{background:#ffffff}"
                             "QListWidget::item:selected:!active{background:#ffffff}");
    checkList->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;width:10;height:150;}"
                                                  "QScrollBar::handle{background:#e1e1e2; border:2px solid transparent; border-radius:5px;}"
                                                  "QScrollBar::handle:hover{background:#cfcfd1}"
                                                  "QScrollBar::sub-line{background:transparent}"
                                                  "QScrollBar::add-line{background:transparent}");

    content_Layout->setSpacing(0);
    content_Layout->addWidget(description);
    content_Layout->addWidget(checkList);


    //buttom
    m_Buttom = new QFrame(this);
    m_Buttom->setFixedHeight(60);
    m_Buttom->setStyleSheet("QFrame{background:#f5f5f7}");
    buttom_Layout = new QHBoxLayout(m_Buttom);
    m_ackBtn = new QPushButton("确认",this);
    m_ackBtn->setFixedSize(80,30);
    m_ackBtn->setStyleSheet("QPushButton{background:#0c73c2;color:#ffffff;border-radius:3}");
    m_addDirBtn = new QPushButton("添加文件夹",this);
    m_addDirBtn->setFixedSize(80,30);
    m_addDirBtn->setStyleSheet("QPushButton{background:#ffffff;border-radius:3}");
    buttom_Layout->addWidget(m_ackBtn);
    buttom_Layout->addWidget(m_addDirBtn);
    buttom_Layout->setMargin(0);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_Title);
    mainLayout->addWidget(m_Content);
    mainLayout->addWidget(m_Buttom);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    connect(m_closeBtn,&QPushButton::clicked,this,&SelectDirFrame::close);
    connect(m_addDirBtn,&QPushButton::clicked,this,&SelectDirFrame::slot_addDir);

    readSettings();
}

void SelectDirFrame::mousePressEvent(QMouseEvent *event)
{
    if(QRect(0,0,300,50).contains(event->pos()))
    {
        FramelessWidget::mousePressEvent(event);
    }
}

void SelectDirFrame::slot_addDir()
{
    QString DirName = QFileDialog::getExistingDirectory(this, "打开本地歌曲文件夹","/home",
                                                    QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);

    if(DirName.isEmpty() || AllDirList.contains(DirName))
        return;

    QListWidgetItem *item = new QListWidgetItem;
    QCheckBox *checkBox = new QCheckBox;
    checkBox->setText(DirName);
    checkBox->setToolTip(DirName);
    checkList->addItem(item);
    checkList->setItemWidget(item,checkBox);
    checkBox->setChecked(true);
}

void SelectDirFrame::getCheckedState()
{
    int count = checkList->count();
    DirList.clear();
    MusicPathList.clear();
    AllDirList.clear();
    for(int i=0; i<count; ++i)
    {
         QListWidgetItem *item = checkList->item(i);
         QWidget *widget = checkList->itemWidget(item);
         QCheckBox *box = reinterpret_cast<QCheckBox*>(widget);

         MusicPath tmpPath;
         if(box->isChecked())
         {
            DirList.append(box->text());

            tmpPath.path = box->text();
            tmpPath.ischecked = true;
            MusicPathList.append(tmpPath);
         }
         else
         {
            tmpPath.path = box->text();
            tmpPath.ischecked = false;
            MusicPathList.append(tmpPath);
         }
         AllDirList.append(box->text());
    }
    QSettings settings;
    settings.beginWriteArray("music_path");
    for(int i=0; i<MusicPathList.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("path",MusicPathList.at(i).path);
        settings.setValue("ischecked",MusicPathList.at(i).ischecked);
    }
    settings.endArray();
}

void SelectDirFrame::writeSettings()
{
    QSettings settings;
    settings.beginGroup("select_widget");
    settings.setValue("pos", pos());
    settings.endGroup();
}

void SelectDirFrame::readSettings()
{
    QSettings settings;
    settings.beginGroup("select_widget");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    settings.endGroup();
    move(pos);
}

void SelectDirFrame::closeEvent(QCloseEvent *event)
{
  Q_UNUSED(event);
  writeSettings();
}
