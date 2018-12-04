#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = nullptr);
    ~ClickLabel();

signals:
    void clicked();

protected:
    virtual void mousePressEvent(QMouseEvent *);
};

#endif // CLICKLABEL_H
