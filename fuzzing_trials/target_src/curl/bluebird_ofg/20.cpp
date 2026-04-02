#include <cstddef>
#include <cstdint>
#include <cstring>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated to be used as a C string.
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test with the input string.
    curl_global_trace(inputString);

    // Clean up the allocated memory.
    delete[] inputString;

    return 0;
}