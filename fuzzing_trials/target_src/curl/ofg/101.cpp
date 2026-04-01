#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    long timeout;

    if (multi_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    CURLMcode result = curl_multi_timeout(multi_handle, &timeout);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}