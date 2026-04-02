#include <cstdint>
#include <curl/curl.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    curl_socket_t sockfd;
    void *sockptr;

    // Initialize CURLM handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize sockfd and sockptr with non-null values
    sockfd = (curl_socket_t)((size > 0) ? data[0] : 0);
    sockptr = (void *)((size > 1) ? &data[1] : &data[0]);

    // Call the function-under-test
    CURLMcode result = curl_multi_assign(multi_handle, sockfd, sockptr);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}