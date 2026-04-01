#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    curl_socket_t sockfd;
    void *sockptr;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // For fuzzing, use the first few bytes of data as the socket descriptor and pointer
    if (size >= sizeof(curl_socket_t) + sizeof(void *)) {
        sockfd = *(reinterpret_cast<const curl_socket_t *>(data));
        sockptr = *(reinterpret_cast<void *const *>(data + sizeof(curl_socket_t)));

        // Call the function-under-test
        curl_multi_assign(multi_handle, sockfd, sockptr);
    }

    // Cleanup
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}