#include <cstddef>
#include <cstdint>
#include <curl/curl.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    CURL *curl;
    char *escaped_str;

    // Initialize CURL
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Ensure that the input data is null-terminated before passing it as a string
    char *input_str = new char[size + 1];
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Call the function-under-test
    escaped_str = curl_easy_escape(curl, input_str, static_cast<int>(size));

    // Clean up
    if (escaped_str) {
        curl_free(escaped_str);
    }
    curl_easy_cleanup(curl);
    delete[] input_str;

    return 0;
}