#include <cstdint>
#include <cstddef>
#include <cstring>  // Include this for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    CURL *curl;
    char *escaped_str;
    const char *input_str;
    int length;

    // Initialize a CURL handle
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Ensure the input data is null-terminated for use as a C-string
    char *null_terminated_data = new char[size + 1];
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Assign the null-terminated data to input_str
    input_str = null_terminated_data;

    // Use a non-zero length for the fuzzing input
    length = static_cast<int>(size);

    // Call the function-under-test
    escaped_str = curl_easy_escape(curl, input_str, length);

    // Clean up
    if (escaped_str) {
        curl_free(escaped_str);
    }
    curl_easy_cleanup(curl);
    delete[] null_terminated_data;

    return 0;
}