#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

const QString main_style = "QFrame{background:rgb(102,183,255);}";

#pragma pack(push)
#pragma pack(1)

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar(){}

    QLabel *titleIconLabel;
    QLabel *nullLabel;

    QPushButton *leftBtn;
    QPushButton *rightBtn;
    QPushButton *searchBtn;

    QLineEdit *searchEdit;

    QPushButton *userIconBtn;
    QPushButton *loginBtn;
    QPushButton *skinBtn;
    QPushButton *mailBtn;
    QPushButton *setBtn;
    QPushButton *miniBtn;
    QPushButton *minimumBtn;
    QPushButton *maximumBtn;
    QPushButton *closeBtn;


private:
    void initTitle();

    QHBoxLayout *titleLayout;
    QHBoxLayout *searchLayout;
    QHBoxLayout *LayoutLeft;
    QHBoxLayout *LayoutRight;

};

#pragma pack(pop)


#endif // TITLEBAR_H

