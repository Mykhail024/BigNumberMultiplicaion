#include <algorithm>
#include <stdexcept>
#include <qdebug.h>

#include "BigNumber.h"

BigNumber::BigNumber(const size_t &numberOfBits)
{
    if(numberOfBits != 0) {
        m_val.resize(std::ceil(static_cast<double>(numberOfBits) / ONE_BITSET_SIZE));
    }
}

BigNumber::BigNumber(std::string str)
{
    if(str.size() <= ONE_BITSET_SIZE) {
        m_val.push_back(bitset(str));
    } else {
        while(!str.empty() && str[0] == '0') {
            str.erase(str.begin());
        }
        while(str.size() % ONE_BITSET_SIZE != 0) {
            str = '0' + str;
        }
        for(size_t i = 0; i < str.size(); i += ONE_BITSET_SIZE) {
            m_val.push_back(bitset(str.substr(i, ONE_BITSET_SIZE)));
        }
    }
}

std::string BigNumber::toString(const bool &normalize) const
{
    if(this->empty()) return "0";

    std::string result = "";
    for(const auto &block : m_val) {
        result += block.to_string();
    }

    if(normalize) {
        size_t zeroCount;
        for(auto it = result.begin(); it != result.end(); it++) {
            if(*it != '0') {
                zeroCount = it - result.begin();
                break;
            }
        }

        return result.empty() ? "0" : result.substr(zeroCount);
    }
    return result;
}

bool BigNumber::at(const size_t &pos) const
{
    if(pos >= size()) {
         throw std::out_of_range("Index out of bounds");
    }

    return m_val[m_val.size() - 1 - (pos / ONE_BITSET_SIZE)][pos % ONE_BITSET_SIZE];
}

void BigNumber::set(const size_t &pos, const bool &isSet)
{
    if(pos >= size()) {
         throw std::out_of_range("Index out of bounds");
    }
    m_val[m_val.size() - 1 - (pos / ONE_BITSET_SIZE)].set(pos % ONE_BITSET_SIZE, isSet);
}

size_t BigNumber::size() const
{
    return m_val.size() * ONE_BITSET_SIZE;
}

void BigNumber::resize(const size_t &size) {
    if (size > this->size()) {
        size_t newSize = (size - this->size()) / ONE_BITSET_SIZE;

        for (size_t i = 0; i < newSize; i++) {
            m_val.insert(m_val.begin(), bitset());
        }
    }
}

BigNumber BigNumber::operator<<(const size_t &shift) const
{
    BigNumber result(*this);

    for(size_t s = 0; s < shift; s++) {
        bool carry = false;

        for(auto it = result.m_val.begin(); it != result.m_val.end(); it++) {
            bool next_carry = (*it)[ONE_BITSET_SIZE - 1];
            *it <<= 1;

            if (it != result.m_val.begin()) {
                (*(it-1))[0] = carry;
            }

            carry = next_carry;
        }

        if (carry) {
            result.m_val.insert(result.m_val.begin(), bitset(1));
        }
    }

    return result;
}

BigNumber BigNumber::operator>>(const size_t &shift) const
{
    BigNumber result(*this);

    for (size_t i = 0; i < shift; i++) {
        for (size_t j = 0; j < result.m_val.size() - 1; j++) {
            result.m_val[j] >>= 1;
            result.m_val[j][ONE_BITSET_SIZE - 1] = result.m_val[j + 1][0];
        }
        result.m_val[result.m_val.size() - 1] >>= 1;
    }

    return result;
}

BigNumber BigNumber::operator+(const BigNumber &other) const
{
    size_t size = std::max(this->size(), other.size());
    BigNumber result(size);

    bool carry = false;

    for(size_t i = 0; i < size; i++) {
        bool bit1 = i < this->size() ? this->at(i) : false;
        bool bit2 = i < other.size() ? other.at(i) : false;

        bool sum = bit1 ^ bit2 ^ carry;

        result.set(i, sum);

        carry = (bit1 & bit2) | ((bit1 ^ bit2) & carry);
    }

    if (carry) {
        result.m_val.insert(result.m_val.begin(), bitset(1));
    }

    return result;
}

BigNumber BigNumber::operator-(const BigNumber &other) const
{
    size_t size = std::max(this->size(), other.size());
    BigNumber result(size);

    bool borrow = false;
    bool x, y, t;
    for(size_t i = 0; i < size; i++) {
        x = i < this->size() ? this->at(i) : false;
        y = i < other.size() ? other.at(i) : false;

        t = x ^ y ^ borrow;

        result.set(i, t);

        borrow = (borrow && !x) || (!x && y) || (y && borrow);
    }

    return result;
}

BigNumber BigNumber::operator*(const BigNumber &other) const
{
    BigNumber result(this->size() + other.size());

    for (int i = 0; i < this->size(); i++) {
        for (int j = 0; j < other.size(); j++) {
            bool currentBit = at(i) && other.at(j);
            result.set(i + j, result.at(i + j) ^ currentBit);
        }
    }

    result.shrink();

    return result;
}


BigNumber BigNumber::operator+=(const BigNumber &other)
{
    *this = *this + other;
    return *this;
}

void BigNumber::shrink()
{
    size_t count = 0;
    for(auto it = m_val.begin(); it != m_val.end(); it++) {
        if((*it).none()) {
            count++;
        } else {
            break;
        }
    }
    if(count) {
        m_val.erase(m_val.begin(), m_val.begin() + count);
    }
}

bool BigNumber::none() const
{
    for(const auto &el : m_val) {
        if(!el.none()) return false;
    }
    return true;
}

bool BigNumber::any() const
{
    for(const auto &el : m_val) {
        if(el.any()) return true;
    }
    return false;
}

bool BigNumber::all() const
{
    for(const auto &el : m_val) {
        if(!el.all()) return false;
    }
    return true;
}

std::pair<BigNumber, BigNumber> BigNumber::split() const
{
    if(this->empty()) return {BigNumber(), BigNumber()};

    size_t last = this->size()-1;
    while(last >= 0) {
        if(at(last)) break;
        last--;
    }

    if(last > 0) {
        const size_t half = std::ceil((last + 1) / 2);
        BigNumber first(half);
        BigNumber second(half);

        for (size_t i = 0; i <= last; i++) {
            if (i < half) {
                first.set(i, this->at(i));
            } else {
                second.set(i - half, this->at(i));
            }
        }

        return {first, second};
    }
    return {BigNumber(), BigNumber()};
}


bool BigNumber::empty() const
{
    return m_val.empty();
}
