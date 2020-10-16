#include <gtest/gtest.h>
#include <template_common.hpp>
#include <type_traits>

class TypeIdentityTest: public testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

template<class T>
T hello(T a, type_identity_t<T> b) {
    return a + b;
}

TEST_F(TypeIdentityTest, test_identity_convert) {
    {
        float a = 3.0, b = 4.0;
        auto result = hello(a, b);
        bool out = std::is_same_v<decltype(result), float>;
        ASSERT_TRUE(out);
        ASSERT_EQ(result, 7.0);
    }
    {
        int a = 3, b = 4;
        auto result = hello(a, b);
        bool out = std::is_same_v<decltype(result), int>;
        ASSERT_TRUE(out);
        ASSERT_EQ(result, 7);
    }
}
