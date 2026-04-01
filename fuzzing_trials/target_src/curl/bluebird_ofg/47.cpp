#include <cstddef>
#include <cstdint>
#include <cstring>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    char *unescapedString = curl_unescape(inputString, static_cast<int>(size));

    // Clean up
    delete[] inputString;
    if (unescapedString != nullptr) {
        curl_free(unescapedString);
    }

    return 0;
}