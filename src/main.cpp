#include <chrono>
#include <QApplication>

#include "karatsuba.h"

using namespace std::chrono;

int main(int argc, char **argv)
{
    std::string a = "10010101010101001010100101010101";
    std::string b = "10101010110101010101";

    auto start = high_resolution_clock::now();
    std::string result = karatsuba(a, b);
    auto stop = high_resolution_clock::now();

    qDebug() << result;
    qDebug() << "time:" << duration_cast<microseconds>(stop-start).count();
}
