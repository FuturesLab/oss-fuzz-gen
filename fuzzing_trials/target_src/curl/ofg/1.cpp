#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Initialize CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Call the function-under-test
    CURL **handles = curl_multi_get_handles(multi_handle);

    // Check if handles is not NULL and do something with it if needed
    if (handles) {
        // For fuzzing purposes, we can iterate over the handles
        // and perform operations, but here we just demonstrate access
        for (size_t i = 0; handles[i] != NULL; ++i) {
            // Example operation: retrieve information from each handle
            char *url;
            curl_easy_getinfo(handles[i], CURLINFO_EFFECTIVE_URL, &url);
        }
    }

    // Cleanup
    curl_multi_cleanup(multi_handle);

    return 0;
}