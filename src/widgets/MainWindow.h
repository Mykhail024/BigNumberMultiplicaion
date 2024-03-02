#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

class QCustomPlot;

class MainWindow : public QWidget
{
    Q_OBJECT
    public:
        MainWindow();

    public slots:
        void test();
    private:
        QVBoxLayout *m_vlayout;
        QCustomPlot *m_plot;
        QPushButton *m_testButton;
        QLineEdit *m_iterationsCount;

        QVector<double> m_data;
};
