#include <algorithm>

#include "binMultiply.h"
#include "karatsuba.h"

std::string multiply(const std::string &a, const std::string &b) {
    if (a == "0" || b == "0") return "0";

    std::string result = "0";

    for (int i = a.size() - 1; i >= 0; i--) {
        std::string tempVal;
        int carry = 0;

        for (int j = b.size() - 1; j >= 0; j--) {
            int mult = (a[i] - '0') * (b[j] - '0') + carry;
            tempVal = char(mult % 2 + '0') + tempVal;
            carry = mult / 2;
        }

        if (carry > 0) {
            tempVal = char(carry + '0') + tempVal;
        }

        tempVal += std::string(a.size() - i - 1, '0');
        result = add(result, tempVal);
    }

    return result;
}
