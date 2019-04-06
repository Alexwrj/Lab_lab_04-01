#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QtCharts/QChartView>
#include <QSlider>
#include <QSpinBox>
#include <QValueAxis>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class Model : public QObject
{
    Q_OBJECT
public:
    Model();
    Model(QChart *chart, QDoubleSpinBox *b, QSpinBox *t, QDoubleSpinBox *r, QDoubleSpinBox *a, QValueAxis *axisX, QValueAxis *axisY);

public slots:
    void simulationBegin();

private:
    QDoubleSpinBox *b, *r, *a;
    QSpinBox *t;
    const int N0 = 100;
    QVector<int> simulate();
    QChart *ctx;
    QLineSeries *series;
    QValueAxis *axisX, *axisY;
};

#endif // MODEL_H
