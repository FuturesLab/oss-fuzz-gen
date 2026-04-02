#include "curl/curl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
        CURLM *multi_handle = NULL;
        CURL *easy_handle = NULL;
        CURLMcode result;

        // Initialize CURLM and CURL handles
        multi_handle = curl_multi_init();
        if (!multi_handle) {
            return 0;
        }

        easy_handle = curl_easy_init();
        if (!easy_handle) {
            curl_multi_cleanup(multi_handle);
            return 0;
        }

        // Set a URL for the easy handle, using data as a dummy URL
        // Ensure the URL is null-terminated and non-empty
        if (size > 0) {
            char *url = (char *)malloc(size + 1);
            if (url) {
                memcpy(url, data, size);
                url[size] = '\0'; // Null-terminate the string
                curl_easy_setopt(easy_handle, CURLOPT_URL, url);
                free(url);
            }
        } else {
            curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");
        }

        // Add the easy handle to the multi handle
        result = curl_multi_add_handle(multi_handle, easy_handle);

        // Perform the request
        int still_running;
        do {

            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of curl_multi_perform
            int acivnytf = 1;
            result = curl_multi_perform(multi_handle, &acivnytf);
            // End mutation: Producer.REPLACE_ARG_MUTATOR


        } while (result == CURLM_OK && still_running);

        // Cleanup
        curl_multi_remove_handle(multi_handle, easy_handle);
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);

        return 0;
    }
}