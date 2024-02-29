#pragma once

#include <QString>
#include <qtypes.h>

#include <vector>
#include <bitset>

class BigNumber
{
    public:
        static constexpr size_t ONE_BITSET_SIZE = 512;

        BigNumber(const size_t &numberOfBits);
        BigNumber(std::string str);

        size_t size() const;
        void resize(const size_t &size);
        bool empty() const;

        std::string toString(const bool &normalize = true) const;

        void shrink();

        bool at(const size_t &pos) const;
        void set(const size_t &pos, const bool &val);
        bool none() const;
        bool any() const;
        bool all() const;

        std::pair<BigNumber, BigNumber> split() const;

        BigNumber operator<<(const size_t &shift) const;
        BigNumber operator>>(const size_t &shift) const;
        BigNumber operator+(const BigNumber &other) const;
        BigNumber operator+=(const BigNumber &other);
        BigNumber operator-(const BigNumber &other) const;
        BigNumber operator*(const BigNumber &other) const;

    private:
        BigNumber() = default;

        using bitset = std::bitset<ONE_BITSET_SIZE>;
        using long_value = std::vector<bitset>;

        long_value m_val;
};
