#include <cstddef>
#include <cstdint>
#include <cstring>

// Assuming the function is part of a C library
extern "C" {
    const char ** lou_getEmphClasses(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a C string
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    const char **result = lou_getEmphClasses(inputString);

    // Clean up
    delete[] inputString;

    // Return 0 to indicate no error
    return 0;
}