#pragma once

#include <string>

#define D(char) (char - '0')
#define C(char) (char + '0')

std::string add(std::string a, std::string b);
std::string sub(std::string a, std::string b);
std::string shift_left(std::string a, const size_t n);
std::string karatsuba(std::string a, std::string b);
std::string multiply(std::string a, std::string b);
std::pair<std::string, std::string> split(std::string str);
const size_t adjustSize(std::string &a, std::string &b);
std::string decToBin(long long int num);
