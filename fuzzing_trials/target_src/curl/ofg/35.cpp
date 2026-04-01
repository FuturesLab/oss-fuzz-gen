#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    curl_socket_t sockfd;
    int running_handles;
    int action;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Ensure size is sufficient to extract meaningful values
    if (size < sizeof(curl_socket_t) + sizeof(int)) {
        curl_multi_cleanup(multi_handle);
        curl_global_cleanup();
        return 0;
    }

    // Extract values from data
    sockfd = *(curl_socket_t *)data;
    action = *(int *)(data + sizeof(curl_socket_t));

    // Call the function-under-test
    curl_multi_socket_action(multi_handle, sockfd, action, &running_handles);

    // Cleanup
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}