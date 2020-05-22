#include "lightchart.h"

LightChart::LightChart(QWidget *parent) : QWidget(parent)
{
    lightchart=new Chart(this);
    lightchart->initChart();
    lightchart->testFun();
    lightchart->setGeometry(0,0,900,500);
    lightchart->setXYTitle("光照(lc)","时间");
    lightchart->setYRange(0,10000);
}
