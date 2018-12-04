#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QFrame>
#include <QVector>
#include <QLabel>
#include <QToolBar>
#include <QPropertyAnimation>
#include <QResizeEvent>

const int image_count = 6;
const int center_width = 542;
const int center_hieght =  200;
const int margin_height = 188;

class AnimationWidget : public QFrame
{
    Q_OBJECT

private:
    int margin_width = 110;
    int default_choose = 0;

public:
    AnimationWidget(QWidget *parent = nullptr);
    ~AnimationWidget();

protected slots:
    void onHoverAction();
private:
    void moveLeft();
    void moveRight();

    QRect center_rect;
    QRect left_rect;
    QRect right_rect;

    QLabel *center_label;
    QLabel *left_label;
    QLabel *right_label;

    QPropertyAnimation *moveAnimation;
    QPropertyAnimation *moveAnimation_left;
    QPropertyAnimation *moveAnimation_right;

    QToolBar *transferBar;
    QVector<QPixmap> label_group;
    QAction *lineAction[image_count];


    void resizeEvent(QResizeEvent*);
};

#endif // ANIMATIONWIDGET_H
