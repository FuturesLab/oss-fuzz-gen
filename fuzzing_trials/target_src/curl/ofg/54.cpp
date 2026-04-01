#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    int running_handles;

    // Initialize the CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Call the function-under-test
    CURLMcode result = curl_multi_socket_all(multi_handle, &running_handles);

    // Cleanup
    curl_multi_cleanup(multi_handle);

    return 0;
}