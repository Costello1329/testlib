#ifndef TESTLIB_MALLOC_ALLOCATOR_H
#define TESTLIB_MALLOC_ALLOCATOR_H

#include <sstream>
#include <string>
#include <vector>
#include <iosfwd>



template <typename vt>
struct malloc_allocator {
    typedef vt value_type;
    vt* allocate (const size_t n) { return reinterpret_cast<vt*>(malloc(n * sizeof(vt))); }
    void deallocate (vt* ptr, const size_t) { return free(ptr); }
};

template <typename vt, typename vt2>
bool operator == (const malloc_allocator<vt>&, const malloc_allocator<vt2>&) noexcept {
    return true;
}

template <typename vt, typename vt2>
bool operator != (const malloc_allocator<vt>& first, const malloc_allocator<vt2>& second) noexcept {
    return !operator==(first, second);
}

typedef std::basic_string<char, std::char_traits<char>, malloc_allocator<char>> malloc_string;

typedef std::basic_stringstream<
    char,
    std::char_traits<char>,
    malloc_allocator<char>
> malloc_stringstream;

template <typename vt>
using malloc_vector = std::vector<vt, malloc_allocator<vt>>;


#endif /// TESTLIB_MALLOC_ALLOCATOR_H.
