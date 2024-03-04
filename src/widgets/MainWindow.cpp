#include <QApplication>
#include <QValidator>
#include <QtConcurrent/QtConcurrent>
#include <QThread>

#include <chrono>

#include "qcustomplot.h"
#include "../math/karatsuba.h"
#include "../math/binMultiply.h"

#include "MainWindow.h"

using namespace std::chrono;

std::string generateBinaryString(const int &size) {
    std::string binaryString;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < size; ++i) {
        int bit = std::rand() % 2;
        binaryString += std::to_string(bit);
    }

    return binaryString;
}

TestThread::TestThread(QObject *parent) : QThread(parent){}

void TestThread::run()
{
    emit started();
    progressMaxValChanged(1);
    progressValChanged(1);
    progressTextChanged("Generating keys");
    m_results.keys.clear();
    for(int i = m_start; i <= m_stop; i += m_step) {
        m_results.keys.push_back(i);
    }

    int maxProgress = m_results.keys.size() * m_itCount * 2;
    int curentProgress = 0;

    progressMaxValChanged(maxProgress);

    m_results.dataKaratsuba.clear();
    for(int i = 0; i < m_results.keys.size(); i++) {
        double averageTime = 0;
        for(int j = 0; j < m_itCount; j++) {
            progressValChanged(++curentProgress);
            progressTextChanged(QString("Testing Karatsuba. Test %1 of %2 (%3/%4)").arg(i).arg(m_results.keys.size()-1).arg(j).arg(m_itCount));
            const std::string str1 = generateBinaryString(m_results.keys[i]);
            const std::string str2 = generateBinaryString(m_results.keys[i]);

            auto start = high_resolution_clock::now();
            karatsuba(str1, str2);
            auto stop = high_resolution_clock::now();

            averageTime += duration_cast<milliseconds>(stop-start).count();
        }
        m_results.dataKaratsuba.push_back(averageTime/m_itCount);
    }


    m_results.dataLong.clear();
    for(int i = 0; i < m_results.keys.size(); i++) {
        double averageTime = 0;
        for(int j = 0; j < m_itCount; j++) {
            progressValChanged(++curentProgress);
            progressTextChanged(QString("Testing Long. Test %1 of %2 (%3/%4)").arg(i).arg(m_results.keys.size()-1).arg(j).arg(m_itCount));
            const std::string str1 = generateBinaryString(m_results.keys[i]);
            const std::string str2 = generateBinaryString(m_results.keys[i]);

            auto start = high_resolution_clock::now();
            multiply(str1, str2);
            auto stop = high_resolution_clock::now();

            averageTime += duration_cast<milliseconds>(stop-start).count();
        }
        m_results.dataLong.push_back(averageTime/m_itCount);
    }

    progressValChanged(maxProgress);
    progressTextChanged("Testing finished!");
    emit finished(m_results);
}

TestThread::testResults TestThread::getResults() const
{
    return m_results;
}

void TestThread::setInfo(const int start, const int stop, const int step, const int itCount)
{
    m_start = start;
    m_stop = stop;
    m_step = step;
    m_itCount = itCount;
}

MainWindow::MainWindow()
    : QWidget()
    , m_vlayout(new QVBoxLayout(this))
    , m_testButton(new QPushButton("Test", this))
    , m_iterationsCount(new QLineEdit(this))
    , m_startIt(new QLineEdit(this))
    , m_endIt(new QLineEdit(this))
    , m_stepIt(new QLineEdit(this))
    , m_progressBar(new QProgressBar(this))
    , m_testThread(new TestThread(this))
{
    this->setWindowTitle("Big Number Multiplication");

    auto *validator = new QIntValidator(0, INT_MAX, m_iterationsCount);

    m_iterationsCount->setValidator(validator);
    m_startIt->setValidator(validator);
    m_endIt->setValidator(validator);
    m_stepIt->setValidator(validator);

    m_progressBar->setTextVisible(true);
    m_progressBar->setFormat("Press test");
    m_progressBar->setAlignment(Qt::AlignCenter);
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(1);
    m_progressBar->setValue(1);
    m_progressBar->setMinimumWidth(350);

    m_vlayout->addWidget(new QLabel("Iteration Count", this));
    m_vlayout->addWidget(m_iterationsCount);
    m_vlayout->addWidget(new QLabel("Digits count of first number", this));
    m_vlayout->addWidget(m_startIt);
    m_vlayout->addWidget(new QLabel("Digits count of last number", this));
    m_vlayout->addWidget(m_endIt);
    m_vlayout->addWidget(new QLabel("Step", this));
    m_vlayout->addWidget(m_stepIt);
    m_vlayout->addWidget(m_progressBar);
    m_vlayout->addWidget(m_testButton, 0, Qt::AlignTop);

    connect(m_testButton, &QPushButton::clicked, this, &MainWindow::test);
    connect(m_testThread, &TestThread::started, this, [&]{ setControlsEnabled(false); });
    connect(m_testThread, &TestThread::finished, this, &MainWindow::testEnd);
    connect(m_testThread, &TestThread::progressValChanged, m_progressBar, &QProgressBar::setValue);
    connect(m_testThread, &TestThread::progressTextChanged, m_progressBar, &QProgressBar::setFormat);
    connect(m_testThread, &TestThread::progressMaxValChanged, m_progressBar, &QProgressBar::setMaximum);
}

void MainWindow::test()
{
    if(m_iterationsCount->text().isEmpty() || m_startIt->text().isEmpty() || m_endIt->text().isEmpty() || m_stepIt->text().isEmpty()) return;

    const int itStart = m_startIt->text().toInt();
    const int itStop = m_endIt->text().toInt();
    const int itStep = m_stepIt->text().toInt();
    const int itCount = m_iterationsCount->text().toInt();

    m_testThread->setInfo(itStart, itStop, itStep, itCount);
    m_testThread->start(QThread::HighestPriority);
}


void MainWindow::testEnd(TestThread::testResults results)
{
    if(m_plot) {
        m_plot->deleteLater();
    }

    m_plot = new QCustomPlot(this);
    m_plot->setMinimumHeight(350);
    m_plot->setMinimumWidth(600);
    m_plot->addGraph();

    m_plot->graph(0)->setPen(QPen(QColor("blue")));
    m_plot->graph(0)->setName("Karatsuba multiplication");
    m_plot->graph(0)->setData(results.keys, results.dataKaratsuba);

    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(QColor("red")));
    m_plot->graph(1)->setName("Long multiplication");
    m_plot->graph(1)->setData(results.keys, results.dataLong);

    m_plot->yAxis->setLabel("Time (ms)");
    m_plot->xAxis->setLabel("Digits in number");
    m_plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    m_plot->legend->setVisible(true);

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    m_plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(5, 0, 5, 5));
    subLayout->addElement(0, 0, m_plot->legend);

    m_plot->plotLayout()->setRowStretchFactor(1, 0.001);

    m_plot->graph(0)->rescaleAxes(true);
    m_plot->graph(1)->rescaleAxes();

    m_vlayout->addWidget(m_plot);
    setControlsEnabled(true);
}

void MainWindow::setControlsEnabled(const bool &val)
{
    m_testButton->setEnabled(val);
    m_startIt->setEnabled(val);
    m_endIt->setEnabled(val);
    m_iterationsCount->setEnabled(val);
    m_stepIt->setEnabled(val);
}
