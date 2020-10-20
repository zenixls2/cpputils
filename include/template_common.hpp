#pragma once

#if __cplusplus > 201703L // c++20 code

#include<type_traits>
#include<array>

#else // __cplusplus

namespace std {
template<class T>
struct type_identity {
    using type = T;
};

// explicit deduction
template<class... Ts> visit_lambda(Ts...) -> visit_lambda<Ts...>;

namespace {
template<typename S>
struct array_proxy {};

template<template<typename, std::size_t> class S, typename T, std::size_t N>
struct array_proxy<S<T, N>> {
    std::string value;
    operator std::array<T, N>() const {
        std::array<T, N> lhs;
        size_t end = std::min(N-1, value.size());
        for (size_t i=0; i<end; ++i) {
            lhs[i] = value[i];
        }
        for (size_t i=end; i<N; ++i) {
            lhs[i] = 0;
        }
        return lhs;
    }
};

}

// convert string to specific size of array.
template<typename T>
auto to_array(const std::string& v) -> array_proxy<T> { return {v}; }

} // namespace std

#endif // __cplusplus

namespace std {

// helper type for visitor
// usage:
// std::visit(visit_lambda {
//     [](auto arg) { std::cout << arg; },
//     [](double arg) { std::cout << std::fixed << arg; },
//     [](const std::string& arg) { std::cout << std::quoted(arg); },
// }, v);
template<class... Ts> struct visit_lambda : Ts... { using Ts::operator()...; };

template<class T>
using type_identity_t = typename type_identity<T>::type;

template<class... Args>
constexpr bool always_false = false;

template<class... Args>
constexpr bool always_true = true;

} // namespace std
