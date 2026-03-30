#include <stdio.h>
#include <stdlib.h>
#include "curl/curl.h"
#include <stdint.h> // Include for uint8_t

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;

    // Initialize CURL globally
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        return 0;
    }

    // Initialize a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Initialize an easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        curl_global_cleanup();
        return 0;
    }

    // Set options for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");
    
    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the request, this is where fuzzing can be applied
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}