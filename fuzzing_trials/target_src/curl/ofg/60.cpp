#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib> // Include for malloc and free

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Ensure the input data is null-terminated for string operations
    char *input = static_cast<char *>(malloc(size + 1));
    if (!input) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Prepare an integer pointer for the output length
    int output_length = 0;

    // Call the function-under-test
    char *unescaped = curl_easy_unescape(curl, input, static_cast<int>(size), &output_length);

    // Clean up
    if (unescaped) {
        curl_free(unescaped);
    }
    free(input);
    curl_easy_cleanup(curl);

    return 0;
}