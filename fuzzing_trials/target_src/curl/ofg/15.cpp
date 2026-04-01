#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Create a CURL easy handle and add it to the multi handle
    CURL *easy_handle = curl_easy_init();
    if (easy_handle) {
        curl_multi_add_handle(multi_handle, easy_handle);
    }

    // Call the function-under-test
    CURL **handles = curl_multi_get_handles(multi_handle);

    // Clean up
    if (easy_handle) {
        curl_multi_remove_handle(multi_handle, easy_handle);
        curl_easy_cleanup(easy_handle);
    }
    curl_multi_cleanup(multi_handle);

    return 0;
}