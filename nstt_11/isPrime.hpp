#ifndef ISPRIME_HPP
#define ISPRIME_HPP

#include <type_traits>

template <int N, int M>
struct isDivisible
        : std::conditional_t<(M == 1),
                std::false_type,
                std::conditional_t<(N % M == 0),
                        std::true_type,
                        isDivisible<N, M - 1>>> {};

template <int N>
struct isPrime
        : std::conditional_t<(N < 2),
                std::false_type,
                std::conditional_t<!isDivisible<N, N / 2>::value,
                        std::true_type,
                        std::false_type>> {};

template <int num, int cur = 2, int count = 0>
struct getNthPrime
        : std::conditional_t<isPrime<cur>::value,
                std::conditional_t<(num == count + 1),
                        std::integral_constant<int, cur>,
                        getNthPrime<num, cur + 1, count + 1>>,
                getNthPrime<num, cur + 1, count>> {};

#endif // ISPRIME_HPP