#pragma once
#include <valarray>
#include <type_traits>
#include <iostream>
#include <limits>
#include <sstream>
#include <cmath>
#include <exception>
#include <functional>
extern "C" {
#include <quadmath.h>
}
#pragma push_macro("assert")
#pragma push_macro("__STR")
#pragma push_macro("STR")
#undef assert
#undef STR
#undef __STR
#define __STR(a) #a
#define STR(a) __STR(a)
#define assert_m(condition, msg) \
    if(!(condition)) throw std::runtime_error(STR(condition) " fails, " msg);
#define assert(condition) \
    if (!(condition)) throw std::runtime_error(STR(condition) " fails" );

namespace std {
extern __float128 ceil(__float128 arg);
extern __float128 floor(__float128 arg);
extern __float128 fabs(__float128 arg);
extern __float128 abs(const __float128& arg);
extern __float128 log(const __float128& arg);
extern __float128 ldexp(__float128 arg, int exp);
extern __float128 sqrt(const __float128& arg);
extern __float128 exp(const __float128& arg);
extern __float128 pow(__float128 arg, __float128 exp);
extern __float128 sin(const __float128& arg);
extern __float128 acos(const __float128& arg);
extern __float128 erfc(const __float128& arg);
extern __float128 erf(const __float128& arg);
extern bool isnan(const __float128& arg);
extern std::string to_string(const __float128& arg);
} // namespace std
template<>
class std::numeric_limits<__float128> {
public:
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr bool has_denorm = std::denorm_present;
    static constexpr int digits = 113;
    static constexpr int digits10 = 33;
    static constexpr int max_digits10 = 36;
    static constexpr int radix = 2;
    static constexpr __float128 min() {
        return FLT128_MIN;
    }
    static constexpr __float128 max() {
        return FLT128_MAX;
    }
    static constexpr __float128 epsilon() {
        return FLT128_EPSILON;
    }
    static __float128 quiet_NaN() {
        return nanq("");
    }
    static constexpr __float128 infinity() {
        return 1.0Q / 0.0Q;
    }
};

extern __float128 upgrade(float k);
extern __float128 upgrade(double k);
extern __float128 upgrade(long double k);
extern __float128 upgrade(int k);
extern __float128 upgrade(uint32_t k);

template<class CharType, class CharTrait>
std::basic_ostream<CharType, CharTrait>& operator<<(
        std::basic_ostream<CharType, CharTrait>& os, __float128 value) {
    size_t precision = os.precision();
    std::string format = "%";
    auto flags = os.flags();
    if (std::ios_base::showpos & flags)
        format += "+";

    if (std::ios_base::showpoint & flags)
        format += "#";

    format += ".*Q";
    if (std::ios_base::scientific & flags)
        format += "e";
    else if (std::ios_base::fixed & flags)
        format += "f";
    else
        format += "g";
    char buffer[128] = {0};
    quadmath_snprintf(buffer, 128, format.c_str(), precision, value);
    os << buffer;
    return os;
}

template<class CharType, class CharTrait>
std::basic_istream<CharType, CharTrait>& operator>>(
        std::basic_istream<CharType, CharTrait>& is, __float128& value) {
    std::string str;
    is >> str;
    value = strtoflt128(str.data(), NULL);
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {
    bool printed = false;
    os << "[";
    for (auto& x: arr) {
        if (printed) os << ", ";
        else printed = true;
        os << x;
    }
    os << "]";
    return os;
}

// allows you to do std::valarray operations on float128.


#pragma pop_macro("__STR")
#pragma pop_macro("STR")
#pragma pop_macro("assert")
