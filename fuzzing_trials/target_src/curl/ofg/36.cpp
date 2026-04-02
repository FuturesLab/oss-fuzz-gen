#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize CURL globally
    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (res != CURLE_OK) {
        return 0; // If initialization fails, exit early
    }

    // Create a CURL easy handle
    CURL *curl = curl_easy_init();
    if(curl) {
        // Set options for the CURL easy handle
        // Assume the input data is a URL
        char *url = (char *)malloc(size + 1);
        if (url == NULL) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 0;
        }
        memcpy(url, data, size);
        url[size] = '\0';

        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Clean up
        free(url);
        curl_easy_cleanup(curl);
    }

    // Cleanup CURL globally
    curl_global_cleanup();

    return 0;
}