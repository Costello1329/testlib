#ifndef TESTLIB_UTILS_H
#define TESTLIB_UTILS_H

#include <string>
#include <cmath>



namespace __utils {
    std::string bool_to_string (const bool val) noexcept { return val ? "true" : "false"; }

    std::string wrap_front (const std::string& str) {
        return std::string(" ").append(str);
    }

    std::string wrap_back (const std::string& str) {
        return std::string(str).append(" ");
    }
    std::string wrap (const std::string& str) {
        return std::string(" ").append(str).append(" ");
    }

    bool cmp_double (const double first, const double second, const double eps = 1e-6) noexcept {
        return std::fabs(first - second) < eps;
    }

    template <typename vt>
    std::string ptr_to_string (vt* const ptr) {
        std::stringstream ss;
        ss << static_cast<const int*>(ptr);
        return ss.str();
    }
} /// namespace __utils.


#endif /// TESTLIB_UTILS_H.
