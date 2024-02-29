#include <QApplication>
#include <bits/chrono.h>
#include <chrono>
#include <cstdlib>
#include <qlogging.h>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

#include "math.h"

using namespace std::chrono;

/*
BigNumber karatsuba(BigNumber x, BigNumber y)
{
    if(x.size() > y.size()) {
        y.resize(x.size());
    } else if(x.size() < y.size()){
        x.resize(y.size());
    }
    const size_t n = x.size();

    if(n <= BigNumber::ONE_BITSET_SIZE) {
        return x * y;
    }

    auto [Xl, Xr] = x.split();
    auto [Yl, Yr] = y.split();

    auto P1 = karatsuba(Xl, Yl);
    auto P2 = karatsuba(Xr, Yr);
    auto P3 = karatsuba(Xl+Xr, Yl+Yr);

    return ((P1 << 2*(n-n/2)) + P2) + ((P3 - (P1 + P2)) << n-(n/2));
}
*/
int main(int argc, char **argv)
{/*
    BigNumber a("10010101010101001010100101010101101110111100100100010111010101000100100010100010001101110111100100100010111010101000100100010100010001101110111100100100010111010101000100100010100010001101110111100100100010111010101000100100010100010001");
    BigNumber b("10101010110101010101101110111100100100010111010101000100100010100010001101110111100100100010111010101000100100010100010001101110111100100100010111010101000100100010100010001");

    auto start = high_resolution_clock::now();
    auto SR = a*b;
    auto stop = high_resolution_clock::now();
    auto sr_time = duration_cast<microseconds>(stop-start);

    start = high_resolution_clock::now();
    auto karR = karatsuba(a, b);
    stop = high_resolution_clock::now();
    auto kar_time = duration_cast<microseconds>(stop-start);

    qDebug() << "/////////////KARATSUBA/////////////////";
    qDebug() << karR.toString();
    qDebug() << "/////////////STANDARD/////////////////";
    qDebug() << SR.toString();
    qDebug() << "///////////////TIME///////////////////";
    qDebug() << "Karatsuba:" << kar_time.count();
    qDebug() << "Standard:" << sr_time.count();

    std::bitset<0> g;
*/

/*
    BigNumber a(50);
    std::cout << a.toString(false) << std::endl;

    size_t i = 0;
    bool inc = true;
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        a.set(i, inc);
        std::cout << a.toString(false) << std::endl;
        if(i < a.size()-1) {
            i++;
        } else {
            i = 0;
            inc = !inc;
        }
    }*/
}
