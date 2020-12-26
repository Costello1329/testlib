#ifndef TESTLIB_RANDOM_H
#define TESTLIB_RANDOM_H

#include <numeric>
#include <random>



namespace __random {
    template<typename T>
    T get_random_int_number (
        const T &min = std::numeric_limits<T>::min(),
        const T &max  = std::numeric_limits<T>::min()
    ) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dis(min, max);
        return dis(gen);
    }

    template<typename T>
    T get_random_real_number (
        const T &min = std::numeric_limits<T>::min(),
        const T &max  = std::numeric_limits<T>::min()
    ) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(min, max);
        return dis(gen);
    }

    bool toss_coin () { return get_random_int_number<int>(0, 1) == 1; }
} /// namespace __random.


#endif /// TESTLIB_RANDOM_H.
