#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string, ensuring it's null-terminated
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    char *result = curl_unescape(input, static_cast<int>(size));

    // Free the result if it is not NULL
    if (result != nullptr) {
        curl_free(result);
    }

    // Clean up
    delete[] input;

    return 0;
}