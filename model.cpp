#include "model.h"
#include "math.h"
#include <QDebug>
#include <QValueAxis>

Model::Model()
{

}

Model::Model(QChart *chart, QDoubleSpinBox *b, QSpinBox *t, QDoubleSpinBox *r, QDoubleSpinBox *a, QValueAxis *axisX, QValueAxis * axisY)
{
    this->ctx = chart;
    this->b = b;
    this->t = t;
    this->r = r;
    this->a = a;
    this->axisX = axisX;
    this->axisY = axisY;
}

void Model::simulationBegin()
{
    QVector<int> values = simulate();

    ctx->removeAllSeries();

    series = new QLineSeries();
    series->setName("Популяция");

    float second = 0.f;
    float fl_t = t->text().toFloat();
    for (auto &val : values)
    {
        series->append(static_cast<qreal>(second), static_cast<qreal>(val));
        qDebug() << val << ", " << second << "\n";
        second += fl_t;
    }

    ctx->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

QVector<int> Model::simulate()
{
    QVector<int> population(100);

    population[0] = N0;

    float fl_a = static_cast<float>(a->value());
    float fl_b = static_cast<float>(b->value());
    float fl_r = static_cast<float>(r->value());

    for (int i = 1; i < population.size(); i++)
    {
        population[i] = static_cast<int>((population[i - 1] * fl_r) / (1.f + pow(fl_a * population[i - 1], fl_b)));
    }

    return population;
}
