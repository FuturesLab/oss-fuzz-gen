#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Initialize CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (multi_handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Call the function under test
    CURL **handles = curl_multi_get_handles(multi_handle);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}