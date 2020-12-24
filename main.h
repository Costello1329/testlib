#ifndef TESTLIB_MAIN_H
#define TESTLIB_MAIN_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <string>
#include <chrono>



#define START_TESTS \
    size_t ___test_num = 0; \
    std::string ___test_name; \

/**
 * Should be used only by automatic
 * external testlib-translator module.
 */
#define START_TESTS_FROM(___first_test_num) \
    size_t ___test_num = ___first_test_num - 1; \
    std::string ___test_name; \

#define END_TESTS \
    std::exit(0);

#define START_TEST(___name) \
    { \
        ssize_t subtest_index = -1; \
        std::string ___subtest_name; \
        auto ___test_started = std::chrono::high_resolution_clock::now(); \
        ___test_name = ___name; \
        std::cout << \
            "Test " << \
            (___test_num + 1) << \
            " (" << \
            ___test_name << \
            ") started" << \
            std::endl;

#define END_TEST \
        std::cout << "Passed in "; \
        const auto ___test_runtime = \
            std::chrono::duration_cast<std::chrono::milliseconds>( \
                std::chrono::high_resolution_clock::now() - ___test_started \
            ).count(); \
        if (___test_runtime < 100) \
            std::cout << std::to_string(___test_runtime) << "ms"; \
        else \
            std::cout << \
                std::setprecision(1) << \
                std::fixed << \
                (___test_runtime / 1000.) << \
                "s"; \
        std::cout << std::endl << std::endl; \
        ++ ___test_num; \
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
        std::cout << std::endl << ___msg << std::endl; \
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
    ___ammounts.emplace_back(___amount); \
    ___names.emplace_back(___name);

#define END_SUBTESTS_DECLARATION \
    if (___i == 0) { \
        assert(___total_ammount == ___r); \
        ___r ++; \
    } \
    /**
     * Need to wrap in order to isolate ___prefix_sum variable,
     * because it's a non-context variable and shouldn't be seen.
     */ \
    { \
        size_t ___prefix_sum = 0; \
        for (size_t ___j = 0; ___j < ___names.size(); ___j ++) { \
            ___prefix_sum += ___ammounts[___j]; \
            if (___prefix_sum == ___i) { \
                std::cout << \
                    "Subtest " << \
                    (___j + 1) << \
                    " (" << \
                    ___names[___j] << \
                    ") passed" << \
                    std::endl; \
            } \
            else if (___i < ___prefix_sum) { \
                subtest_index = ___j; \
                ___subtest_name = ___names[___j]; \
                break; \
            } \
        } \
    } \
    if (___i == ___r - 1) \
        break;

#define PROVIDE_TEST_CONTEXT \
    ___test_num, ___test_name

#define RECEIVE_TEST_CONTEXT \
    const size_t& ___test_num, const std::string& ___test_name

#define EXTERNAL_SUBTEST_HANDLERS_START \
    { \
        size_t ___handled_subtests_amount = 0; \

#define EXTERNAL_SUBTEST_HANDLERS_END \
    }

#define START_EXTERNAL_SUBTEST_HANDLER(___subtests_amount) \
    { \
        const size_t ___current_handler_subtests_amount = ___subtests_amount; \
        ___handled_subtests_amount += ___subtests_amount; \
        if ( \
            subtest_index >= ___handled_subtests_amount - ___subtests_amount && \
            subtest_index < ___handled_subtests_amount \
        ) { \
            subtest_index -= (___handled_subtests_amount - ___subtests_amount);

#define END_EXTERNAL_SUBTEST_HANDLER \
            subtest_index += (___handled_subtests_amount - ___current_handler_subtests_amount); \
        } \
    }

#define PROVIDE_SUBTEST_CONTEXT \
    subtest_index, ___subtest_name

#define RECEIVE_SUBTEST_CONTEXT \
    const ssize_t& subtest_index, const std::string& ___subtest_name


#endif /// TESTLIB_MAIN_H.
