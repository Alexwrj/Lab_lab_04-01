#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView();
    ChartView(QChart *chart, QWidget *parent = nullptr);

protected:
    virtual bool viewportEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

private:
    bool m_isTouching;
    bool m_isDragging;
    float m_posX;
    float m_posY;

    float m_dragFactor = 0.3f;
};

#endif // CHARTVIEW_H
