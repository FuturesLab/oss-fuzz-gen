#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
    #include "/src/liblouis/liblouis/liblouis.h"  // Correct path for formtype and lou_getTypeformForEmphClass
}

// Fuzzer harness
extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for two null-terminated strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two strings
    size_t mid = size / 2;

    // Allocate memory for the two strings
    char *str1 = new char[mid + 1];
    char *str2 = new char[size - mid + 1];

    // Copy the data into the strings and null-terminate them
    std::memcpy(str1, data, mid);
    str1[mid] = '\0';

    std::memcpy(str2, data + mid, size - mid);
    str2[size - mid] = '\0';

    // Call the function-under-test
    formtype result = lou_getTypeformForEmphClass(str1, str2);

    // Clean up
    delete[] str1;
    delete[] str2;

    return 0;
}