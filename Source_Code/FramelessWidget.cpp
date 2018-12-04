#include "FramelessWidget.h"

FramelessWidget::FramelessWidget(QWidget *parent) : QWidget(parent)
{
    m_border=18;
    m_state.MousePressed=false;
    m_state.IsPressBorder=false;

    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void FramelessWidget::mouseMoveRect(const QPoint &p)
{
    if(!m_state.IsPressBorder)
    {
        if((p.x()>width()-m_border) && (p.y()>height()-m_border))
        {
            setCursor(Qt::SizeFDiagCursor);
            m_curPos=CursorPos::BottomRight;
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    else
    {
        switch (m_curPos)
        {
            case CursorPos::BottomRight:
            {
                int setW=QCursor::pos().x()-x();
                int setH=QCursor::pos().y()-y();
                setGeometry(m_state.WindowPos.x(),m_state.WindowPos.y(),setW,setH);
                emit sig_PosChange(setW,setH);
                break;
            }
            default:
                break;
        }
    }
}

void FramelessWidget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    if (event->button() == Qt::LeftButton)
    {
        m_state.WindowPos = this->pos();
        if(     QRect(0,0,width(),height()-m_border*2).contains(event->pos())
           ||   QRect(0,height()-m_border*2,width()-2*m_border,m_border*2).contains(event->pos())
          )
        {
            m_state.MousePos = event->globalPos();
            m_state.MousePressed = true;
        }
        else if(QRect(width()-m_border*2,height()-m_border*2,m_border*2,m_border*2).contains(event->pos()))
        {
            m_state.IsPressBorder=true;
        }
    }
}

void FramelessWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_state.IsPressBorder=false;
        m_state.MousePressed=false;
    }
}

void FramelessWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseMoveRect(mapFromGlobal(QCursor::pos()));
    if (m_state.MousePressed)
    {
        this->move(m_state.WindowPos + (event->globalPos() - m_state.MousePos));
    }
}
