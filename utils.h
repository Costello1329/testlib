#ifndef TESTLIB_UTILS_H
#define TESTLIB_UTILS_H

#include <string>
#include <cmath>



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

    double cmp_double (const double first, const double second, const double eps = 1e-6) {
        return std::fabs(first - second) < eps;
    }
} /// namespace __utils.


#endif /// TESTLIB_UTILS_H.
