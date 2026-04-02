#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

// Ensure the C library is compatible with C++ linkage
extern "C" {
#include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (multi_handle == NULL) {
        return 0;
    }

    // Initialize CURL easy handle
    CURL *easy_handle = curl_easy_init();
    if (easy_handle == NULL) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Set a dummy URL, since we need a valid URL for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Initialize the number of running handles
    int still_running = 0;

    // Call the function-under-test
    CURLMcode result = curl_multi_perform(multi_handle, &still_running);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}