#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/liblouis/liblouis/liblouis.h"  // Correct path for the header file
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 5) return 0;

    // Extract parameters from data
    const char *dots = reinterpret_cast<const char*>(data);
    size_t dots_len = strlen(dots);
    if (dots_len >= size) return 0;  // Ensure the string is null-terminated within bounds

    // Allocate widechar buffers
    widechar output1[256];
    widechar output2[256];

    // Set arbitrary values for the int parameters
    int param1 = 1;
    int param2 = 1;

    // Call the function-under-test
    lou_dotsToChar(dots, output1, output2, param1, param2);

    return 0;
}