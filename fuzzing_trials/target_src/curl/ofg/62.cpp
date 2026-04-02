#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    CURL *easy_handle = curl_easy_init();
    struct curl_waitfd waitfd;
    int numfds;
    CURLMcode result;

    if (multi_handle == NULL || easy_handle == NULL) {
        if (multi_handle) curl_multi_cleanup(multi_handle);
        if (easy_handle) curl_easy_cleanup(easy_handle);
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *url = (char *)malloc(size + 1);
    if (!url) {
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set up the easy handle with the URL
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    curl_easy_setopt(easy_handle, CURLOPT_FOLLOWLOCATION, 1L);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Initialize the curl_waitfd structure
    waitfd.fd = 0; // File descriptor, assuming standard input for simplicity
    waitfd.events = CURL_WAIT_POLLIN; // Interested in reading
    waitfd.revents = 0; // Will be filled with the actual events

    // Use the size of data as the timeout value for fuzzing
    unsigned int timeout_ms = (unsigned int)(size % 1000); // Limit timeout to 1000ms for fuzzing

    // Call the function-under-test
    result = curl_multi_poll(multi_handle, &waitfd, 1, timeout_ms, &numfds);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    free(url);

    return 0;
}