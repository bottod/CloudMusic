#include "ClickLabel.h"

ClickLabel::ClickLabel(QWidget *parent)
    : QLabel (parent)
{

}

ClickLabel::~ClickLabel()
{

}

void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit clicked();

    QLabel::mousePressEvent(event);
}
