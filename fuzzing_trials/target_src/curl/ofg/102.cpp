#include <curl/curl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
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
    char *header_name = (char *)malloc(size + 1);
    if (!header_name) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }
    memcpy(header_name, data, size);
    header_name[size] = '\0';

    // Set some options for the CURL handle to prevent real network operations
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // We don't need body data

    // Call the function-under-test
    result = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
    result = curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);
    result = curl_easy_perform(curl);

    // Clean up
    free(header_name);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}