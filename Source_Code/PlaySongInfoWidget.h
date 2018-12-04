#ifndef PLAYSONGINFOWIDGET_H
#define PLAYSONGINFOWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontMetrics>
#include "ClickLabel.h"

class PlaySongInfoWidget : public QFrame
{
    Q_OBJECT
public:
    explicit PlaySongInfoWidget(QWidget *parent = nullptr);
    ~PlaySongInfoWidget();

    QPushButton *songNameBtn, *singleNameBtn, *loveBtn, *shareBtn;
    ClickLabel *cdLabel;

    void setSongText(QString,QString);

private:
    void initWidget();

    QHBoxLayout *h_mainLayout;
    QVBoxLayout *v_initLayout1, *v_initLayout2;
};

#endif // PLAYSONGINFOWIDGET_H
