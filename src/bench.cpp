#include "old_cstring.h"
#include "cstring.h"
#include "hash.h"
#include <chrono>

using namespace std::chrono_literals;

namespace {
cstring test_unique_long_new() {
    auto string = new char[256];
    std::memset(string, 'A', 255);
    string[255] = '\0';

    return cstring::own(string, 255);
}

old::cstring test_unique_long_old() {
    auto string = new char[256];
    std::memset(string, 'A', 255);
    string[255] = '\0';

    return old::cstring(string);
}

cstring test_unique_short_new() {
    auto string = new char[4];
    std::memset(string, 'A', 3);
    string[3] = '\0';

    return cstring::own(string, 3);
}

old::cstring test_unique_short_old() {
    auto string = new char[4];
    std::memset(string, 'A', 3);
    string[3] = '\0';

    return old::cstring(string);
}

cstring test_shared_long_new() {
    auto string = new char[256];
    std::memset(string, 'A', 255);
    string[255] = '\0';

    cstring result(string);
    delete[] string;
    return result;
}

old::cstring test_shared_long_old() {
    auto string = new char[256];
    std::memset(string, 'A', 255);
    string[255] = '\0';

    old::cstring result(string);
    delete[] string;
    return result;
}

cstring test_shared_short_new() {
    auto string = new char[4];
    std::memset(string, 'A', 3);
    string[3] = '\0';

    cstring result(string);
    delete[] string;

    return result;
}

old::cstring test_shared_short_old() {
    auto string = new char[4];
    std::memset(string, 'A', 3);
    string[3] = '\0';

    old::cstring result(string);
    delete[] string;

    return result;
}

cstring test_literal_long_new() {
    return "Teeeeeest sssstring";
}

old::cstring test_literal_long_old() {
    return "Teeeeeest sssstring";
}

cstring test_literal_short_new() {
    return "A";
}

old::cstring test_literal_short_old() {
    return "A";
}
} // namespace

volatile const char *g_char_p;
volatile std::size_t g_integer;


namespace {
using chrono_clock = std::chrono::high_resolution_clock;

constexpr std::size_t iterations = 4000000;

void test_unique_long() {
    chrono_clock::duration new_duration, old_duration;

    {
        auto start = chrono_clock::now();

        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_unique_long_old().c_str();
        }

        old_duration = chrono_clock::now() - start;
    }

    {
        auto start = chrono_clock::now();
        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_unique_long_new().c_str();
        }

        new_duration = chrono_clock::now() - start;
    }


    std::printf("%18s %8zu %8zu\n", "test_unique_long",
        static_cast<std::size_t>(old_duration.count() / iterations),
        static_cast<std::size_t>(new_duration.count() / iterations));
}

void test_unique_short() {
    chrono_clock::duration new_duration, old_duration;

    {
        auto start = chrono_clock::now();

        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_unique_short_old().c_str();
        }

        old_duration = chrono_clock::now() - start;
    }

    {
        auto start = chrono_clock::now();
        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_unique_short_new().c_str();
        }

        new_duration = chrono_clock::now() - start;
    }


    std::printf("%18s %8zu %8zu\n", "test_unique_short",
        static_cast<std::size_t>(old_duration.count() / iterations),
        static_cast<std::size_t>(new_duration.count() / iterations));
}

void test_shared_long() {
    chrono_clock::duration new_duration, old_duration;

    {
        auto start = chrono_clock::now();

        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_shared_long_old().c_str();
        }

        old_duration = chrono_clock::now() - start;
    }

    {
        auto start = chrono_clock::now();
        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_shared_long_new().c_str();
        }

        new_duration = chrono_clock::now() - start;
    }


    std::printf("%18s %8zu %8zu\n", "test_shared_long",
        static_cast<std::size_t>(old_duration.count() / iterations),
        static_cast<std::size_t>(new_duration.count() / iterations));
}

void test_shared_short() {
    chrono_clock::duration new_duration, old_duration;

    {
        auto start = chrono_clock::now();

        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_shared_short_old().c_str();
        }

        old_duration = chrono_clock::now() - start;
    }

    {
        auto start = chrono_clock::now();
        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_shared_short_new().c_str();
        }

        new_duration = chrono_clock::now() - start;
    }


    std::printf("%18s %8zu %8zu\n", "test_shared_short",
        static_cast<std::size_t>(old_duration.count() / iterations),
        static_cast<std::size_t>(new_duration.count() / iterations));
}

void test_literal_long() {
    chrono_clock::duration new_duration, old_duration;

    {
        auto start = chrono_clock::now();

        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_literal_long_old().c_str();
        }

        old_duration = chrono_clock::now() - start;
    }

    {
        auto start = chrono_clock::now();
        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_literal_long_new().c_str();
        }

        new_duration = chrono_clock::now() - start;
    }


    std::printf("%18s %8zu %8zu\n", "test_literal_long",
        static_cast<std::size_t>(old_duration.count() / iterations),
        static_cast<std::size_t>(new_duration.count() / iterations));
}

void test_literal_short() {
    chrono_clock::duration new_duration, old_duration;

    {
        auto start = chrono_clock::now();

        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_literal_short_old().c_str();
        }

        old_duration = chrono_clock::now() - start;
    }

    {
        auto start = chrono_clock::now();
        for (std::size_t i = 0; i < iterations; ++i) {
            g_char_p = test_literal_short_new().c_str();
        }

        new_duration = chrono_clock::now() - start;
    }


    std::printf("%18s %8zu %8zu\n", "test_literal_short",
        static_cast<std::size_t>(old_duration.count() / iterations),
        static_cast<std::size_t>(new_duration.count() / iterations));
}
}

int main() {
    std::printf("%18s %8s %8s\n", "Name", "Old", "New");
    test_unique_long(); clear_cstring_cache(); old::clear_cstring_cache();
    test_unique_short(); clear_cstring_cache(); old::clear_cstring_cache();
    test_shared_long(); clear_cstring_cache(); old::clear_cstring_cache(); 
    test_shared_short(); clear_cstring_cache(); old::clear_cstring_cache();
    test_literal_long(); clear_cstring_cache(); old::clear_cstring_cache();
    test_literal_short(); clear_cstring_cache(); old::clear_cstring_cache();

    return 0;
}
