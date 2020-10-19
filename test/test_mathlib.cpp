#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <functional>
#include <mathlib.hpp>

class MathlibTest: public testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

template <typename T>
std::string float2string(const T a_value) {
    std::ostringstream out;
    out.precision(16);
    out << std::fixed << a_value;
    return out.str();
}

TEST_F(MathlibTest, test_print) {
    std::string value = std::to_string(3.q);
    ASSERT_EQ(value, "3");
    value = std::to_string(-4.2q);
    ASSERT_EQ(value, "-4.2");
    value = std::to_string(-3.141592653589793q);
    ASSERT_EQ(value, "-3.141592653589793");
}

TEST_F(MathlibTest, test_precision) {
}

TEST_F(MathlibTest, test_downgrade) {
    double price = 22.1;
    double price2 = double(22.1q);
    ASSERT_EQ(price, price2);

    ASSERT_EQ(float2string(22.1l), "22.1000000000000000");
    ASSERT_EQ(float2string(26.5), "26.5000000000000000");
    ASSERT_EQ(float2string(22.1q), "22.1000000000000000");
}

TEST_F(MathlibTest, test_upgrade) {
    double a = 0.12326378;
    double b = 0.001001;
    std::stringstream s1, s2;
    s1.precision(22);
    s1 << 0.12326378q * 0.001001q;
    s2.precision(22);
    s2 << (upgrade(a) * upgrade(b));
    ASSERT_EQ(0.12326378q * 0.001001q - upgrade(a) * upgrade(b), 0.q);
    ASSERT_EQ(s1.str(), s2.str());
    long double aa = 0.1234567L;
    ASSERT_EQ(0.1234567q * 0.1234567q, upgrade(aa) * upgrade(aa));

    double c = 0;
    ASSERT_EQ(upgrade(c), 0.q);

    long double cc = 1e-1023L;
    ASSERT_EQ(upgrade(cc), 1e-1023q);
}
