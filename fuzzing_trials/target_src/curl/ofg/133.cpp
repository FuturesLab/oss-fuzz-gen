#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    CURL *easy_handle = curl_easy_init();

    if (multi_handle && easy_handle) {
        // Add the easy handle to the multi handle
        curl_multi_add_handle(multi_handle, easy_handle);

        // Call the function-under-test
        curl_multi_remove_handle(multi_handle, easy_handle);

        // Clean up
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
    }

    return 0;
}