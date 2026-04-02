#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURLMcode result;

    // Initialize CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // If initialization fails, return early
    }

    // Ensure there is enough data to extract a CURLMoption and a void* pointer
    if (size < sizeof(CURLMoption) + sizeof(void*)) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Extract a CURLMoption from the data
    CURLMoption option = *(CURLMoption *)data;

    // Extract a void* pointer from the data
    void *ptr = (void *)(data + sizeof(CURLMoption));

    // Call curl_multi_setopt with extracted option and pointer
    result = curl_multi_setopt(multi_handle, option, ptr);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}