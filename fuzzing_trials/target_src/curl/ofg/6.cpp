#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Ensure the size is sufficient for splitting the data
    if (size < 2) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Split the data into two parts for the unsigned char inputs
    size_t half_size = size / 2;
    const unsigned char *part1 = data;
    size_t part1_size = half_size;
    const unsigned char *part2 = data + half_size;
    size_t part2_size = size - half_size;

    // Create a non-NULL string for the second parameter
    const char *dummy_string = "dummy_string";

    // Call the function-under-test
    res = curl_easy_ssls_import(curl, dummy_string, part1, part1_size, part2, part2_size);

    // Cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}