#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Initialize libcurl
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Create a fake socket using the data
    curl_socket_t sockfd = CURL_SOCKET_BAD;
    if (size >= sizeof(curl_socket_t)) {
        sockfd = *(const curl_socket_t *)data;
    }

    // Create an integer pointer
    int action = CURL_POLL_NONE;
    if (size >= sizeof(curl_socket_t) + sizeof(int)) {
        action = *(const int *)(data + sizeof(curl_socket_t));
    }

    // Ensure action is within valid range
    action = action % (CURL_POLL_INOUT + 1);

    // Call the function-under-test
    curl_multi_socket(multi_handle, sockfd, &action);

    // Cleanup
    curl_multi_cleanup(multi_handle);

    return 0;
}