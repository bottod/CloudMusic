#ifndef SELECTDIRFRAME_H
#define SELECTDIRFRAME_H


#include "FramelessWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSettings>
#include <QCloseEvent>

//for setting to write
struct MusicPath
{
    QString path;
    bool ischecked;
};

#pragma pack(push)
#pragma pack(1)
class SelectDirFrame : public FramelessWidget
{
    Q_OBJECT
public:
    explicit SelectDirFrame(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *);

    QStringList DirList; // all checked dir
    QList<MusicPath> MusicPathList; //all dir with checkable info
    QStringList AllDirList; //all dir without checkable info

    void getCheckedState();

    QPushButton *m_ackBtn;//确认按钮

private slots:
    void slot_addDir();

protected:
    void closeEvent(QCloseEvent *event);

public:
    QListWidget *checkList;
private:
    QFrame *m_Title;
    QLabel *seleLocalDir;
    QPushButton *m_closeBtn;
    QHBoxLayout *title_Layout;

    QFrame *m_Content;
    QLabel  *description;
    QVBoxLayout *content_Layout;

    QFrame *m_Buttom;
    QPushButton *m_addDirBtn;
    QHBoxLayout *buttom_Layout;

    QVBoxLayout *mainLayout;


    //write conf in ~/.config
    void writeSettings();
    void readSettings();

};

#pragma pack(pop)

#endif // SELECTDIRFRAME_H
