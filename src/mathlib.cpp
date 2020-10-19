#include <mathlib.hpp>

namespace std {
__float128 ceil(__float128 arg) {
    return ceilq(arg);
}

__float128 floor(__float128 arg) {
    return floorq(arg);
}

__float128 fabs(__float128 arg) {
    return fabsq(arg);
}

__float128 abs(const __float128& arg) {
    return fabsq(arg);
}

__float128 log(const __float128& arg) {
    return logq(arg);
}

__float128 ldexp(__float128 arg, int exp) {
    return ldexpq(arg, exp);
}

__float128 sqrt(const __float128& arg) {
    return sqrtq(arg);
}

__float128 exp(const __float128& arg) {
    return expq(arg);
}

__float128 pow(__float128 arg, __float128 exp) {
    return powq(arg, exp);
}

__float128 sin(const __float128& arg) {
    return sinq(arg);
}

__float128 acos(const __float128& arg) {
    return acosq(arg);
}

__float128 erfc(const __float128& arg) {
    return erfcq(arg);
}

__float128 erf(const __float128& arg) {
    return erfq(arg);
}

bool isnan(const __float128& arg) {
    return isnanq(arg);
}

std::string to_string(const __float128& arg) {
    std::stringstream ss;
    char buffer[128] = {0};
    quadmath_snprintf(buffer, 128, "%.*Qg", 33, arg);
    ss << buffer;
    return ss.str();
}

} // namespace std

__float128 upgrade(float k) {
    if (k == 0) return 0.q;
    int i = ceil(std::ilogb(k) * log10(2.0L));
    int g = std::numeric_limits<float>::digits10;
    if (i > g) {
        __float128 p = roundq(powq(10.q, i-g));
        return roundq(__float128(k) / p) * p;
    } else {
        __float128 p = roundq(powq(10.q, g-i));
        return roundq(__float128(k) * p) / p;
    }
}

__float128 upgrade(double k) {
    if (k == 0) return 0.q;
    int i = ceil(std::ilogb(k) * log10(2.0L));
    int g = std::numeric_limits<double>::digits10;
    if (i > g) {
        __float128 p = roundq(powq(10.q, i-g));
        return roundq(__float128(k) / p) * p;
    } else {
        __float128 p = roundq(powq(10.q, g-i));
        return roundq(__float128(k) * p) / p;
    }
}

__float128 upgrade(long double k) {
    if (k == 0L) return 0.q;
    int i = ceil(std::ilogb(k) * log10(2.0L));
    int g = std::numeric_limits<long double>::digits10;
    if (i > g) {
        __float128 p = roundq(powq(10.q, i-g));
        return roundq(__float128(k) / p) * p;
    } else {
        __float128 p = roundq(powq(10.q, g-i));
        return roundq(__float128(k) * p) / p;
    }
}

__float128 upgrade(int k) {
    return roundq(__float128(k));
}

__float128 upgrade(uint32_t k) {
    return roundq(__float128(k));
}
