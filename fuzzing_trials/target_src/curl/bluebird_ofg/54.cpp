#include <cstddef>
#include <cstdint>
#include <cstring>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string and ensure it is null-terminated
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test with the input string and its size
    char *result = curl_unescape(input, static_cast<int>(size));

    // Clean up
    delete[] input;
    if (result) {
        curl_free(result);
    }

    return 0;
}