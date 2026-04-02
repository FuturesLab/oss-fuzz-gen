#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURLMcode result;
    curl_socket_t sockfd;
    void *sockptr;

    // Initialize CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Ensure the data is large enough to extract a socket descriptor
    if (size < sizeof(curl_socket_t)) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Extract socket descriptor from data
    sockfd = *(const curl_socket_t *)data;

    // Assign a pointer from the remaining data or a dummy pointer
    if (size > sizeof(curl_socket_t)) {
        sockptr = (void *)(data + sizeof(curl_socket_t));
    } else {
        sockptr = (void *)0x1;  // Use a non-NULL dummy pointer
    }

    // Call the function-under-test
    result = curl_multi_assign(multi_handle, sockfd, sockptr);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}