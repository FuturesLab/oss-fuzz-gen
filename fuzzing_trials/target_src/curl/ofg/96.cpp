#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    char *escaped_str = curl_escape(input, static_cast<int>(size));

    // Clean up
    if (escaped_str != nullptr) {
        curl_free(escaped_str);
    }
    delete[] input;

    return 0;
}