#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "/src/curl/include/curl/multi.h"
#include <cstdint>
#include <cstring>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int) + sizeof(curl_socket_t) + sizeof(int)) {
        return 0;
    }

    // Initialize a CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Prepare variables for function calls
    unsigned int notification = 0;
    curl_socket_t sockfd = 0;
    int ev_bitmask = 0;
    int running_handles = 0;

    // Copy data into variables
    std::memcpy(&notification, Data, sizeof(unsigned int));
    std::memcpy(&sockfd, Data + sizeof(unsigned int), sizeof(curl_socket_t));
    std::memcpy(&ev_bitmask, Data + sizeof(unsigned int) + sizeof(curl_socket_t), sizeof(int));

    // Fuzz curl_multi_notify_enable
    curl_multi_notify_enable(multi_handle, notification);

    // Fuzz curl_multi_socket_action
    curl_multi_socket_action(multi_handle, sockfd, ev_bitmask, &running_handles);

    // Fuzz curl_multi_perform
    curl_multi_perform(multi_handle, &running_handles);

    // Fuzz curl_multi_assign
    curl_multi_assign(multi_handle, sockfd, nullptr);

    // Fuzz curl_multi_socket_all
    curl_multi_socket_all(multi_handle, &running_handles);

    // Fuzz curl_multi_notify_disable
    curl_multi_notify_disable(multi_handle, notification);

    // Cleanup
    curl_multi_cleanup(multi_handle);

    return 0;
}