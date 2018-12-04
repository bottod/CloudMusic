#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

class BottomWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void initWidget();
    QHBoxLayout *h_mainLayout,*m_hControlLayout;

public:
    QFrame *m_controlFrame;
    QPushButton *lastBtn, *playBtn, *nextBtn, *volumeBtn, *playModeBtn, *lyricBtn, *listBtn;
    QLabel *startTimeLabel, *endTimeLabel, *bottomRightLabel;
    QSlider *playTimeSlider, *volumeSlider;
};

#endif // BOTTOMWIDGET_H
