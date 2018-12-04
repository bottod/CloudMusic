#ifndef TURNTABLEWIDGET_H
#define TURNTABLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QTimer>
#include <QLabel>

class TurntableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TurntableWidget(QWidget *parent = nullptr);
     QPushButton *hideButton;
     QColor backgroud_color;

     QTimer *record_timer;
     QTimer *stylus_in_timer;

     int record_angle = 0;
     int stylus_angle = 0;

     QLabel *music_titelLabel;
     QLabel *music_erLabel;
     QLabel *special_Label;

     QPixmap pix_cd;

private:
    void paintEvent(QPaintEvent *event);

public slots:
    void update_record();

    void update_stylus_in();
    void update_stylus_out();
};

#endif // LEFT_MUSICSHOWWIDGET_H
