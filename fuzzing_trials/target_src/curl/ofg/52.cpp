#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    curl_socket_t sockfd;
    int running_handles;
    CURLMcode result;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (multi_handle == NULL) {
        curl_global_cleanup();
        return 0;
    }

    // Ensure the socket is not NULL and has a valid value
    sockfd = (curl_socket_t)(size > 0 ? data[0] : 0);

    // Ensure running_handles is not NULL
    running_handles = 1;

    // Call the function-under-test
    result = curl_multi_socket(multi_handle, sockfd, &running_handles);

    // Clean up
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}