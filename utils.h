#ifndef TESTLIB_UTILS_H
#define TESTLIB_UTILS_H

#include <string>



namespace __utils {
    std::string bool_to_string (const bool val) {
        return val ? "true" : "false";
    }

    std::string wrap_front (const std::string& str) {
        return " " + str;
    }

    std::string wrap_back (const std::string& str) {
        return str + " ";
    }

    std::string wrap (const std::string& str) {
        return wrap_front(wrap_back(str));
    }
} /// namespace __utils.


#endif /// TESTLIB_UTILS_H.
