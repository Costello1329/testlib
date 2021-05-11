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

typedef std::basic_string<char, std::char_traits<char>, malloc_allocator<char>> malloc_string;

typedef std::basic_stringstream<
    char,
    std::char_traits<char>,
    malloc_allocator<char>
> malloc_stringstream;

template <typename vt>
using malloc_vector = std::vector<vt, malloc_allocator<vt>>;


#endif /// TESTLIB_MALLOC_ALLOCATOR_H.
