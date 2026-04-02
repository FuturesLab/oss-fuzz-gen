#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    CURL *easy_handle = curl_easy_init();

    if (multi_handle && easy_handle) {
        // Set a URL from the input data
        char *url = (char *)malloc(size + 1);
        if (url) {
            memcpy(url, data, size);
            url[size] = '\0'; // Null-terminate the string

            // Set the URL for the easy handle
            curl_easy_setopt(easy_handle, CURLOPT_URL, url);

            // Add the easy handle to the multi handle
            curl_multi_add_handle(multi_handle, easy_handle);

            // Perform the multi handle actions
            int still_running;
            curl_multi_perform(multi_handle, &still_running);

            // Fuzz the curl_multi_remove_handle function
            CURLMcode result = curl_multi_remove_handle(multi_handle, easy_handle);

            // Handle the result if needed (for debugging purposes)
            if (result != CURLM_OK) {
                // Handle error
            }

            // Clean up
            free(url);
        }

        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
    }

    return 0;
}