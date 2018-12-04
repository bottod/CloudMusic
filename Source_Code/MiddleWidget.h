#ifndef MIDDLEWIDGET_H
#define MIDDLEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "MiddleWidgetLeftList.h"
#include "MiddleWidgetRightStack.h"
#include "SelectDirFrame.h"
#include "PlaySongInfoWidget.h"

class MiddleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MiddleWidget(QWidget *parent = nullptr);

    MiddleWidgetLeftList *m_List;
    MiddleWidgetRightStack *m_Stack;
    PlaySongInfoWidget *m_PlaySongInfoWidget;
    SelectDirFrame *m_SelectDirFrame;

private:
    QHBoxLayout *m_hmainLayout;
    QVBoxLayout *m_vListLayout;

private slots:
    void slot_ackDir();

};

#endif // MIDDLEWIDGET_H
