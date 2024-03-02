#include <cstdint>
#include <sstream>

#include "karatsuba.h"

using string = std::string;

std::pair<string, string> split(string str)
{
    const auto half = str.size()/2;
    return {str.substr(0, half), str.substr(half)};
}

const size_t adjustSize(string &a, string &b)
{
    const size_t len1 = a.size();
    const size_t len2 = b.size();

    if(len1 < len2) {
        a.insert(0, len2 - len1, '0');
        return len2;
    } else if(len1 > len2) {
        b.insert(0, len1 - len2, '0');
    }
    return len1;
}

string add(string a, string b)
{
    string result;
    const size_t size = adjustSize(a, b);
    bool carry = 0;
    for(size_t i = size - 1; i != SIZE_MAX; i--) {
        bool _a = D(a[i]);
        bool _b = D(b[i]);

        bool sum = (_a ^ _b ^ carry);

        result = char(C(sum)) + result;

        carry = (_a&_b) | (_b&carry) | (_a&carry);
    }

    if(carry) {
        result = '1' + result;
    }
    return result;
}

std::string decToBin(long long int num)
{
    string result = "";
    if(num <= 0) {
        return "0";
    } else {
        while(num > 0) {
            result.insert(0, std::to_string(num % 2));
            num /= 2;
        }
        return result;
    }
}

std::string sub(std::string a, std::string b)
{
    const size_t size = adjustSize(a, b);
    int diff;
    string result;

    for(size_t i = size-1; i != SIZE_MAX; i--) {
        diff = D(a[i]) - D(b[i]);
        if(diff >= 0) {
            result.insert(0, decToBin(diff));
        } else {
            for(size_t j = i-1; j != SIZE_MAX; j--) {
                a[j] = C((D(a[j]) - 1) % 10);
                if(a[j] != '1') {
                    break;
                }
            }
            result.insert(0, decToBin(diff+2));
        }
    }
    return result;
}

std::string shift_left(std::string a, const size_t n)
{
    return a.append(n, '0');
}


std::string karatsuba(std::string a, std::string b)
{
    const size_t size = adjustSize(a, b);
    if(size == 0) return "0";

    if(size == 1) {
        return (D(b[0]) == 1) && (D(a[0]) == 1) ? "1" : "0";
    }

    auto [al, ar] = split(a);
    auto [bl, br] = split(b);

    const string p1 = karatsuba(al, bl);
    const string p2 = karatsuba(ar, br);
    const string p3 = karatsuba(add(al, ar), add(bl, br));

    const string rp1 = shift_left(p1, 2*(size-size/2));
    const string rp2 = shift_left(sub(p3, add(p1, p2)), size-(size/2));

    return add(add(rp1, p2), rp2);
}

std::string multiply(std::string a, std::string b)
{

}
