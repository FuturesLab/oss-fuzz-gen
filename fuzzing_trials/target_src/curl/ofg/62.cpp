#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure that the input data is non-null and has a size greater than 0
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Copy the input data to a null-terminated string
    char *input = static_cast<char *>(malloc(size + 1));
    if (input == nullptr) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    char *result = curl_unescape(input, static_cast<int>(size));

    // Free the result if it's not null
    if (result != nullptr) {
        curl_free(result);
    }

    // Free the allocated input
    free(input);

    return 0;
}