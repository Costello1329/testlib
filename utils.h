#ifndef TESTLIB_UTILS_H
#define TESTLIB_UTILS_H

#include <string>



namespace __utils {
    std::string bool_to_string (const bool val) {
        return val ? "true" : "false";
    }
} /// namespace __utils.


#endif /// TESTLIB_UTILS_H.
