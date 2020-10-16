#pragma once

#if __cplusplus > 201703L
    // c++20 code
#include<type_traits>

template<class T>
using type_identity = std::type_identity<T>;

#else // __cplusplus

template<class T>
struct type_identity {
    using type = T;
};

#endif // __cplusplus

template<class T>
using type_identity_t = typename type_identity<T>::type;

template<class... Args>
constexpr bool always_false = false;

template<class... Args>
constexpr bool always_true = true;

