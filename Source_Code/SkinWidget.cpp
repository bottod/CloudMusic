#include "SkinWidget.h"
#include <QtDebug>

SkinWidget::SkinWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(260,169);
    this->hide();

    color1_list<<"rgb(255, 102, 102)"<<"rgb(255, 153, 153)"<<"rgb(255, 153, 220)"<<"rgb(102, 139, 255)"<<"rgb(102, 163, 255)"<<"rgb(102, 194, 255)";
    color1_list<<"rgb(0, 179, 89)"<<"rgb(51, 204, 51)"<<"rgb(204, 163, 0)"<<"rgb(255, 153, 102)"<<"rgb(255, 178, 128)"<<"rgb(255, 102, 51)";

    color2_list<<"rgb(225, 62, 62)"<<"rgb(225, 113, 113)"<<"rgb(225, 113, 180)"<<"rgb(72, 99, 215)"<<"rgb(72, 123, 215)"<<"rgb(72, 154, 215)";
    color2_list<<"rgb(0, 139, 49)"<<"rgb(21, 164, 11)"<<"rgb(174, 123, 0)"<<"rgb(225, 113, 62)"<<"rgb(225, 138, 88)"<<"rgb(225, 62, 11)";

    QVBoxLayout *main_layout = new QVBoxLayout(this);

    textLabel = new QLabel(this);
    textLabel->setText("纯色皮肤");

    QHBoxLayout *first_line = new QHBoxLayout;
    color_label1 = new ClickLabel(this);
    color_label1->setCursor(Qt::PointingHandCursor);
    color_label1->setStyleSheet("QLabel{background-color:rgb(255, 102, 102)}");
    color_label2 = new ClickLabel(this);
    color_label2->setCursor(Qt::PointingHandCursor);
    color_label2->setStyleSheet("QLabel{background-color:rgb(255, 153, 153)}");
    color_label3 = new ClickLabel(this);
    color_label3->setCursor(Qt::PointingHandCursor);
    color_label3->setStyleSheet("QLabel{background-color:rgb(255, 153, 220)}");
    color_label4 = new ClickLabel(this);
    color_label4->setCursor(Qt::PointingHandCursor);
    color_label4->setStyleSheet("QLabel{background-color:rgb(102, 139, 255)}");
    color_label5 = new ClickLabel(this);
    color_label5->setCursor(Qt::PointingHandCursor);
    color_label5->setStyleSheet("QLabel{background-color:rgb(102, 163, 255)}");
    color_label6 = new ClickLabel(this);
    color_label6->setCursor(Qt::PointingHandCursor);
    color_label6->setStyleSheet("QLabel{background-color:rgb(102, 194, 255)}");
    first_line->addWidget(color_label1);
    first_line->addWidget(color_label2);
    first_line->addWidget(color_label3);
    first_line->addWidget(color_label4);
    first_line->addWidget(color_label5);
    first_line->addWidget(color_label6);

    QHBoxLayout *second_line = new QHBoxLayout;
    color_label7 = new ClickLabel(this);
    color_label7->setCursor(Qt::PointingHandCursor);
    color_label7->setStyleSheet("QLabel{background-color:rgb(0, 179, 89)}");
    color_label8 = new ClickLabel(this);
    color_label8->setCursor(Qt::PointingHandCursor);
    color_label8->setStyleSheet("QLabel{background-color:rgb(51, 204, 51)}");
    color_label9 = new ClickLabel(this);
    color_label9->setCursor(Qt::PointingHandCursor);
    color_label9->setStyleSheet("QLabel{background-color:rgb(204, 163, 0)}");
    color_label10 = new ClickLabel(this);
    color_label10->setCursor(Qt::PointingHandCursor);
    color_label10->setStyleSheet("QLabel{background-color:rgb(255, 153, 102)}");
    color_label11 = new ClickLabel(this);
    color_label11->setCursor(Qt::PointingHandCursor);
    color_label11->setStyleSheet("QLabel{background-color:rgb(255, 178, 128)}");
    color_label12 = new ClickLabel(this);
    color_label12->setCursor(Qt::PointingHandCursor);
    color_label12->setStyleSheet("QLabel{background-color:rgb(255, 102, 51)}");
    second_line->addWidget(color_label7);
    second_line->addWidget(color_label8);
    second_line->addWidget(color_label9);
    second_line->addWidget(color_label10);
    second_line->addWidget(color_label11);
    second_line->addWidget(color_label12);

    main_layout->addSpacing(9+4);
    main_layout->addWidget(textLabel);
    main_layout->addSpacing(4);
    main_layout->addLayout(first_line);
    main_layout->addSpacing(4);
    main_layout->addLayout(second_line);
    main_layout->addSpacing(5);

    m_ClickLabelVec<<color_label1<<color_label2<<color_label3<<color_label4<<color_label5<<color_label6<<color_label7<<color_label8<<color_label9<<color_label10<<color_label11<<color_label12;

}
void SkinWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor color(229, 255, 255);
    painter.setPen(QColor(115, 115, 115));
    painter.setBrush(color);
    QRectF rect=QRectF(0,9,260,160);
    painter.drawRoundedRect(rect,7,7);
    QPolygonF polygon;
    polygon<<QPointF(130,0)<<QPointF(120,9)<<QPointF(140,9)<<QPointF(130,0);
    painter.drawPolygon(polygon,Qt::WindingFill);
    painter.restore();

}
