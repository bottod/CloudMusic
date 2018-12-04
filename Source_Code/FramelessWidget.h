#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H


#include <QWidget>
#include <QMouseEvent>

//cursor type
enum class CursorPos : char
{
    Default,
    Right,
    Left,
    Bottom,
    Top,
    TopRight,
    TopLeft,
    BottomRight,
    BottomLeft
};

#pragma pack(push)
#pragma pack(1)

//window status
struct pressWindowsState final
{
    bool    MousePressed;
    bool    IsPressBorder;
    QPoint  MousePos;
    QPoint  WindowPos;
};

class FramelessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FramelessWidget(QWidget *parent = nullptr);
    ~FramelessWidget(){}

    void mouseMoveRect(const QPoint &p);

signals:
    void sig_PosChange(int,int);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

    pressWindowsState   m_state;
    int                 m_border;   //right_bottom rect
    CursorPos           m_curPos;
};

#pragma pack(pop)

#endif // FRAMELESSANDAUTOSIZE_H
