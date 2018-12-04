#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QVBoxLayout>
#include "ClickLabel.h"

class SkinWidget: public QWidget
{
    Q_OBJECT
public:
    explicit SkinWidget(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent *event);
public:
    QLabel *textLabel;
    ClickLabel *color_label1, *color_label2, *color_label3, *color_label4, *color_label5, *color_label6;
    ClickLabel *color_label7, *color_label8, *color_label9, *color_label10, *color_label11, *color_label12;
    QVector<ClickLabel*> m_ClickLabelVec;

    QStringList color1_list = {}; //for normal
    QStringList color2_list = {}; //for search edit

};

#endif // SKINWIDGET_H
