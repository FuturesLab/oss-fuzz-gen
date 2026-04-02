#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURLMcode res;
    curl_socket_t sockfd;
    int running_handles;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Use the first byte of data as a curl_socket_t value
    if (size > 0) {
        sockfd = (curl_socket_t)data[0];
    } else {
        sockfd = 0; // Default value if no data
    }

    // Use the second byte of data as an 'events' value
    int events = (size > 1) ? (int)data[1] : 0;

    // Call the function-under-test
    res = curl_multi_socket_action(multi_handle, sockfd, events, &running_handles);

    // Cleanup
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}