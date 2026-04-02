#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    struct curl_waitfd wait_fd;
    int numfds;
    CURLMcode result;

    // Initialize CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Set URL for the easy handle
    // For fuzzing, we can use a fixed URL or construct one from input data
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Initialize curl_waitfd structure
    wait_fd.fd = 0; // File descriptor, 0 indicates standard input
    wait_fd.events = CURL_WAIT_POLLIN; // Wait for input events
    wait_fd.revents = 0; // No events have occurred yet

    // Ensure the size is within a reasonable range for timeout
    int timeout = (size > 0) ? (int)(data[0] % 1000) : 100;

    // Perform the curl operation
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Call the function-under-test
    result = curl_multi_wait(multi_handle, &wait_fd, 1, timeout, &numfds);

    // Cleanup
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}