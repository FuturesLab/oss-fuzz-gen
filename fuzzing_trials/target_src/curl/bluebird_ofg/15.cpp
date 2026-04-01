#include "curl/curl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    void *buffer;
    size_t buffer_size;
    size_t received_size;
    const struct curl_ws_frame *frame;

    // Initialize a CURL handle
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Allocate a buffer for receiving data
    buffer_size = size > 0 ? size : 1; // Ensure buffer size is not zero
    buffer = malloc(buffer_size);
    if (!buffer) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Copy the input data into the buffer
    memcpy(buffer, data, buffer_size);

    // Initialize the received size
    received_size = 0;

    // Set CURL options to prepare for WebSocket receive
    curl_easy_setopt(curl, CURLOPT_URL, "ws://example.com/socket"); // Dummy URL for WebSocket
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

    // Perform the connection
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        free(buffer);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Call the function-under-test
    res = curl_ws_recv(curl, buffer, buffer_size, &received_size, &frame);

    // Clean up
    free(buffer);
    curl_easy_cleanup(curl);

    return 0;
}