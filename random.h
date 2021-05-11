#ifndef TESTLIB_RANDOM_H
#define TESTLIB_RANDOM_H

#include <numeric>
#include <limits>
#include <random>
#include <chrono>

#include "./malloc_allocator.h"



namespace __random {
    auto get_random_seed () {
        static std::random_device rd;
        unsigned long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        return rd() + time;
    }

    template<typename vt>
    vt get_random_int_number (
        const vt &min = std::numeric_limits<vt>::min(),
        const vt &max  = std::numeric_limits<vt>::max()
    ) {
        static std::mt19937 gen(get_random_seed());
        std::uniform_int_distribution<vt> dis(min, max);
        return dis(gen);
    }

    template<typename vt>
    vt get_random_real_number (
        const vt &min = std::numeric_limits<vt>::min(),
        const vt &max  = std::numeric_limits<vt>::min()
    ) {
        static std::mt19937 gen(get_random_seed());
        std::uniform_real_distribution<vt> dis(min, max);
        return dis(gen);
    }

    bool toss_coin () { return get_random_int_number<int>(0, 1) == 1; }

    template <typename vt>
    vt choose_random_element (const std::initializer_list<vt>& il) {
        return malloc_vector<vt>(il)[get_random_int_number<size_t>(0, il.size() - 1)];
    }

    template <typename container>
    typename container::value_type choose_random_element (const container& c) {
        return c[get_random_int_number<size_t>(0, c.size() - 1)];
    }
} /// namespace __random.


#endif /// TESTLIB_RANDOM_H.
