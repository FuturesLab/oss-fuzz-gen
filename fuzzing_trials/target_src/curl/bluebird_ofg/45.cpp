#include <stdint.h>
#include <stdlib.h>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    long timeout;

    // Initialize a CURLM handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // Exit if initialization fails
    }

    // Call the function-under-test
    CURLMcode result = curl_multi_timeout(multi_handle, &timeout);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}