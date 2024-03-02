#include <chrono>

#include "widgets/widgets.h"

using namespace std::chrono;

/*
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QMainWindow window;
  
  // setup customPlot as central widget of window:
  QCustomPlot customPlot;
  window.setCentralWidget(&customPlot);
  
  // create plot (from quadratic plot example):
  QVector<double> x(101), y(101);
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1;
    y[i] = x[i]*x[i];
  }
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(QColor("red")));
  customPlot.graph(0)->setData(x, y);
  customPlot.xAxis->setLabel("x");
  customPlot.yAxis->setLabel("y");
  customPlot.rescaleAxes();
  
  window.setGeometry(100, 100, 500, 400);
  window.show();
  return a.exec();
}*/

int main(int argc, char **argv) {
    return showApp(argc, argv);
}
