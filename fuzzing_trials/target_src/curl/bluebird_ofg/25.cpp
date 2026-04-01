#include "curl/curl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    CURL *curl = NULL;
    CURLcode result;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Ensure data is null-terminated for string operations
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Set some options for the CURL handle to prevent real network operations
    // Use the input data as part of the URL to explore different paths
    char url[256];
    snprintf(url, sizeof(url), "http://example.com/%s", input_data);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // We don't need body data

    // Call the function-under-test
    result = curl_easy_perform(curl);

    // Clean up
    free(input_data);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}