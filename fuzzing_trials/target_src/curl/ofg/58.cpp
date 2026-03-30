#include <cstdint>
#include <cstdlib>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURLMcode result;
    curl_socket_t sockfd;
    void *ptr;

    // Initialize the CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // If initialization fails, exit the fuzzer
    }

    // Ensure the size is sufficient to extract a socket and a pointer
    if (size < sizeof(curl_socket_t) + sizeof(void *)) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Extract a curl_socket_t and a pointer from the data
    sockfd = *(reinterpret_cast<const curl_socket_t *>(data));
    ptr = const_cast<void *>(reinterpret_cast<const void *>(data + sizeof(curl_socket_t)));

    // Call the function-under-test
    result = curl_multi_assign(multi_handle, sockfd, ptr);

    // Clean up the CURL multi handle
    curl_multi_cleanup(multi_handle);

    return 0;
}