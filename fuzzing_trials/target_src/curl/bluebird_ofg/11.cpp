#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    CURLINFO info;
    char *url = "http://example.com";
    long response_code;
    double total_time;
    char *content_type;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the request
        res = curl_easy_perform(curl);

        if(res == CURLE_OK) {
            // Fuzz different CURLINFO options
            info = CURLINFO_RESPONSE_CODE;
            res = curl_easy_getinfo(curl, info, &response_code);
            if(res == CURLE_OK) {
                printf("Response code: %ld\n", response_code);
            }

            info = CURLINFO_TOTAL_TIME;
            res = curl_easy_getinfo(curl, info, &total_time);
            if(res == CURLE_OK) {
                printf("Total time: %.2f\n", total_time);
            }

            info = CURLINFO_CONTENT_TYPE;
            res = curl_easy_getinfo(curl, info, &content_type);
            if(res == CURLE_OK && content_type) {
                printf("Content type: %s\n", content_type);
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}