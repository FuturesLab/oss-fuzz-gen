#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    int still_running = 0;
    CURLMcode mcode;

    // Initialize a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize an easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Set the URL to a non-NULL value
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the multi handle operation
    mcode = curl_multi_perform(multi_handle, &still_running);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}