#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    void *buffer;
    size_t buffer_size;
    size_t n;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Set a dummy URL to initialize the CURL handle
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

    // Allocate a buffer to receive data
    buffer_size = size > 0 ? size : 1; // Ensure buffer size is at least 1
    buffer = malloc(buffer_size);
    if (!buffer) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Copy the input data to the buffer
    memcpy(buffer, data, buffer_size);

    // Perform the curl_easy_recv operation
    res = curl_easy_recv(curl, buffer, buffer_size, &n);

    // Cleanup
    free(buffer);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}