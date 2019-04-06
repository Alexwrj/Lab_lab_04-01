#include "chartview.h"
#include <QDebug>

ChartView::ChartView()
{

}

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    m_isTouching(false)
{
    setMouseTracking(true);
    setRubberBand(QChartView::RectangleRubberBand);
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
            // By default touch events are converted to mouse events. So
            // after this event we will get a mouse event also but we want
            // to handle touch events as gestures only. So we need this safeguard
            // to block mouse events that are actually generated from touch.
            m_isTouching = true;
            m_isDragging = false;

            // Turn off animations when handling gestures they
            // will only slow us down.
            chart()->setAnimationOptions(QChart::NoAnimation);
        }
        return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    m_isDragging = true;
    if (m_isTouching) return;

    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
    {
        if (m_isDragging)
        {
            float deltaX = (event->pos().x() - m_posX) * m_dragFactor;
            float deltaY = (event->pos().y() - m_posY) * m_dragFactor;
            qDebug() << "(" << deltaX << ", " << deltaY << ")";
            chart()->scroll(deltaX, deltaY);
        }
        else
        {
            m_posX = event->pos().x();
            m_posY = event->pos().y();
            return;
        }

        return;
    }

    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    m_isDragging = false;
    if (m_isTouching)
           m_isTouching = false;

       // Because we disabled animations when touch event was detected
       // we must put them back on.
       chart()->setAnimationOptions(QChart::SeriesAnimations);

       QChartView::mouseReleaseEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Plus:
            chart()->zoomIn();
            break;
        case Qt::Key_Minus:
            chart()->zoomOut();
            break;
        case Qt::Key_Left:
            chart()->scroll(-10, 0);
            break;
        case Qt::Key_Right:
            chart()->scroll(10, 0);
            break;
        case Qt::Key_Up:
            chart()->scroll(0, 10);
            break;
        case Qt::Key_Down:
            chart()->scroll(0, -10);
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            break;
    }
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        chart()->zoomIn();
    }
    else if (event->delta() < 0)
    {
        chart()->zoomOut();
    }
}
