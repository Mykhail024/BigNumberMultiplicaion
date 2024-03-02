#include <QApplication>
#include <QValidator>
#include <chrono>

#include "qcustomplot.h"
#include "../math/karatsuba.h"

#include "MainWindow.h"

using namespace std::chrono;

const QVector<double> keys{1, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

std::string generateBinaryString(int size) {
    std::string binaryString;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < size; ++i) {
        int bit = std::rand() % 2;
        binaryString += std::to_string(bit);
    }

    return binaryString;
}

MainWindow::MainWindow()
    : QWidget()
    , m_vlayout(new QVBoxLayout(this))
    , m_testButton(new QPushButton("Test", this))
    , m_iterationsCount(new QLineEdit(this))
{
    this->resize(400, 400);
    this->setWindowTitle("Big Number Product");
    m_iterationsCount->setValidator(new QIntValidator(0, INT_MAX, m_iterationsCount));

    m_vlayout->addWidget(m_iterationsCount);
    m_vlayout->addWidget(m_testButton, 0, Qt::AlignTop);

    connect(m_testButton, &QPushButton::clicked, this, &MainWindow::test);
}

void MainWindow::test()
{
    if(m_iterationsCount->text().isEmpty()) return;

    const int itCount = m_iterationsCount->text().toInt();

    m_data.clear();
    for(size_t i = 0; i < keys.size(); i++) {
        double averageTime = 0;
        for(size_t j = 0; j < itCount; j++) {
            const std::string str1 = generateBinaryString(keys[i]);
            const std::string str2 = generateBinaryString(keys[i]);

            auto start = high_resolution_clock::now();
            karatsuba(str1, str2);
            auto stop = high_resolution_clock::now();

            averageTime += duration_cast<milliseconds>(start-stop).count();
        }
        m_data.push_back(averageTime/itCount);
    }
}

