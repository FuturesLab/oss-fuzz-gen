#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    curl_socket_t sockfd;
    int running_handles;
    CURLMcode result;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Use the first byte of data to determine a socket value
    if (size > 0) {
        sockfd = static_cast<curl_socket_t>(data[0]);
    } else {
        sockfd = 0; // Default to 0 if no data is provided
    }

    // Use the rest of the data to determine the running_handles value
    if (size > 1) {
        running_handles = static_cast<int>(data[1]);
    } else {
        running_handles = 1; // Default to 1 if no additional data is provided
    }

    // Call the function-under-test
    result = curl_multi_socket_action(multi_handle, sockfd, 0, &running_handles);

    // Clean up
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}