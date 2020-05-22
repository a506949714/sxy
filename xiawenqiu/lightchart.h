#ifndef LIGHTCHART_H
#define LIGHTCHART_H

#include <QWidget>
#include "chart.h"

class LightChart : public QWidget
{
    Q_OBJECT
public:
    explicit LightChart(QWidget *parent = nullptr);
    Chart    *lightchart;

signals:

public slots:
};

#endif // LIGHTCHART_H
