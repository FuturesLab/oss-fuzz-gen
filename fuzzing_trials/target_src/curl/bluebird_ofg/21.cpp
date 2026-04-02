#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize variables for the function call
    curl_socket_t sockfd = CURL_SOCKET_BAD;
    int ev_bitmask = 0;
    int running_handles = 0;

    // Ensure we have enough data to extract meaningful values
    if (size >= sizeof(curl_socket_t) + sizeof(int)) {
        sockfd = *(reinterpret_cast<const curl_socket_t*>(data));
        ev_bitmask = *(reinterpret_cast<const int*>(data + sizeof(curl_socket_t)));
    }

    // Call the function-under-test
    CURLMcode result = curl_multi_socket_action(multi_handle, sockfd, ev_bitmask, &running_handles);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}