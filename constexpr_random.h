#ifndef TESTLIB_CONSTEXPR_RANDOM_H
#define TESTLIB_CONSTEXPR_RANDOM_H

#include <iostream>
#include <cstdint>
#include <array>



namespace __constexpr_random {
    static constexpr unsigned lce_a = 4096, lce_c = 150889, lce_m = 714025;

    constexpr static auto time_from_string (const char* str, size_t offset) {
        return
            static_cast<uint32_t>(str[offset] - '0') * 10 +
            static_cast<uint32_t>(str[offset + 1] - '0');
    }

    constexpr static auto get_seed_constexpr () {
        auto time = __TIME__;
        return
            time_from_string(time, 0) * 60 * 60 +
            time_from_string(time, 3) * 60 +
            time_from_string(time, 6);
    }

    constexpr static unsigned uniform_distribution (uint32_t &previous) {
        return previous = ((lce_a * previous + lce_c) % lce_m);
    }

    constexpr static double uniform_distribution_n (unsigned &previous) {
        return static_cast<double>(uniform_distribution(previous)) / lce_m;
    }

    template <typename T, size_t sz>
    constexpr static auto uniform_distribution (T min, T max) {
        std::array<T, sz> dst{};
        auto previous = get_seed_constexpr();

        for (auto &el : dst)
            el = static_cast<T>(uniform_distribution_n(previous) * (max - min) + min);

        return dst;
    }
} /// namespace __constexpr_random.


#endif /// TESTLIB_CONSTEXPR_RANDOM_H.
