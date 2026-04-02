#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    struct curl_waitfd waitfd;
    unsigned int numfds = 1;
    unsigned int timeout_ms = 1000;
    CURLMcode result;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Initialize the curl_waitfd struct with some values
    waitfd.fd = 0; // Typically, a valid file descriptor should be set
    waitfd.events = CURL_WAIT_POLLIN;
    waitfd.revents = 0;

    // Call the function-under-test
    result = curl_multi_waitfds(multi_handle, &waitfd, numfds, &timeout_ms);

    // Clean up
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}