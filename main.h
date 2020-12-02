#ifndef TESTLIB_MAIN_H
#define TESTLIB_MAIN_H

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>



#define START_TESTS \
    size_t ___test_num = 0; \
    std::string ___test_name; \

#define END_TESTS \
    std::cout << "All tests passed" << std::endl; \
    std::exit(0);

#define START_TEST(___name) \
    { \
        ssize_t subtest_index = -1; \
        std::string ___subtest_name; \
        auto ___test_started = std::chrono::high_resolution_clock::now(); \
        ++ ___test_num; \
        ___test_name = ___name; \
        std::cout << "Test " << ___test_num << " (" << ___test_name << ") started" << std::endl;

#define END_TEST \
        auto ___test_runtime = std::chrono::duration_cast<std::chrono::milliseconds>( \
            std::chrono::high_resolution_clock::now() - ___test_started).count(); \
        std::cout << "Test " << ___test_num << " (" << ___test_name << ") passed" << \
        " in " << ___test_runtime << "ms" << std::endl << std::endl; \
    }

#define TEST_FAILED_BASE(___msg) \
    { \
        if (subtest_index != -1) \
            std::cout << \
                "Subtest " << \
                std::to_string(subtest_index + 1) << \
                " (" << \
                ___subtest_name << \
                ") failed:" << \
                std::endl; \
        else \
            std::cout << "Test failed:" << std::endl; \
        std::cout << std::endl << ___msg; \
        exit(1); \
    }

#define TEST_FAILED(___input, ___expected, ___got) \
    { \
        std::stringstream ___str; \
        ___str << \
            "Input: " << ___input << std::endl << \
            "Expected: " << ___expected << std::endl << \
            "Got: " << ___got << std::endl; \
        TEST_FAILED_BASE(___str.str()); \
    }

#define TEST_CORRUPTED \
    std::exit(1);

#define REPEAT(___r_in) \
    { \
        size_t ___r = ___r_in; \
        for (size_t ___i = 0; ___i < ___r; ___i ++) {

#define END_REPEAT \
        } \
    }

#define START_SUBTESTS_DECLARATION \
    size_t ___total_ammount = 0; \
    std::vector<size_t> ___ammounts; \
    std::vector<std::string> ___names;

#define SUBTEST(___name, ___amount) \
    ___total_ammount += ___amount; \
    ___names.emplace_back(___name); \
    ___ammounts.emplace_back(___amount);

#define END_SUBTESTS_DECLARATION \
    if (___i == 0) { \
        assert(___total_ammount == ___r); \
        ___r ++; \
    } \
    size_t ___prefix_sum = 0; \
    for (size_t ___j = 0; ___j < ___names.size(); ___j ++) { \
        ___prefix_sum += ___ammounts[___j]; \
        if (___prefix_sum == ___i) { \
            std::cout << \
                "Subtest " << (___j + 1) << " ("<< ___names[___j] << ") passed" << std::endl; \
        } \
        else if (___i < ___prefix_sum) { \
            subtest_index = ___j; \
            ___subtest_name = ___names[___j]; \
            break; \
        } \
    } \
    if (___i == ___r - 1) \
        break;


#endif /// TESTLIB_MAIN_H.
