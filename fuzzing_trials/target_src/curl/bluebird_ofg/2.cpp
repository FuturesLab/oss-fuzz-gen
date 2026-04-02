#include <stdint.h>
#include <stddef.h>
#include "curl/curl.h"
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Initialize libcurl
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // Return if initialization fails
    }

    // Create a CURL easy handle
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0; // Return if initialization fails
    }

    // Convert the input data to a string and set it as a URL
    char *url = (char *)malloc(size + 1);
    if (!url) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of curl_easy_cleanup
        char bmnovfgc[1024] = "nazkw";
        curl_easy_cleanup(bmnovfgc);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        curl_multi_cleanup(multi_handle);
        return 0; // Return if memory allocation fails
    }
    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the string

    // Set the URL for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // We need a valid integer pointer for the second argument
    int still_running = 0;

    // Call the function-under-test
    CURLMcode result = curl_multi_socket_all(multi_handle, &still_running);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    free(url);

    return 0;
}