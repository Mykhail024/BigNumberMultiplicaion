#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QThread>

class QCustomPlot;

class TestThread : public QThread
{
    Q_OBJECT;
    public:
        TestThread(QObject *parent = nullptr);
        void setInfo(const int start, const int stop, const int step, const int itCount);

        struct testResults {
            QVector<double> keys;
            QVector<double> dataKaratsuba;
            QVector<double> dataLong;
        };

        testResults getResults() const;
    signals:
        void started();
        void finished(testResults results);

        void progressValChanged(const int &val);
        void progressTextChanged(const QString &text);
        void progressMaxValChanged(const int &val);

    protected:
        void run() override;
    private:
        int m_start;
        int m_stop;
        int m_step;
        int m_itCount;
        testResults m_results;
};

class MainWindow : public QWidget
{
    Q_OBJECT
    public:
        MainWindow();

    public slots:
        void test();
        void testEnd(TestThread::testResults results);
    private:
        void setControlsEnabled(const bool &val);

        QVBoxLayout *m_vlayout;
        QCustomPlot *m_plot = nullptr;
        QPushButton *m_testButton;
        QLineEdit *m_iterationsCount;
        QLineEdit *m_startIt;
        QLineEdit *m_endIt;
        QLineEdit *m_stepIt;
        QProgressBar *m_progressBar;

        TestThread *m_testThread;

};
