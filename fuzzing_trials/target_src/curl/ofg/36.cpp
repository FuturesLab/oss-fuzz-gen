#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    curl_socket_t sockfd;
    int ev_bitmask;
    int running_handles;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Use the first byte of data as the socket file descriptor
    sockfd = (curl_socket_t)(data[0]);

    // Use the second byte of data as the event bitmask
    if (size > 1) {
        ev_bitmask = (int)(data[1]);
    } else {
        ev_bitmask = 0;
    }

    // Call the function-under-test
    curl_multi_socket_action(multi_handle, sockfd, ev_bitmask, &running_handles);

    // Clean up
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}