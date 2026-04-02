#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    void *buffer;
    size_t buffer_size = size;
    size_t received_size;
    const struct curl_ws_frame *frame;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Allocate buffer
    buffer = malloc(buffer_size);
    if (!buffer) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Copy data into buffer
    memcpy(buffer, data, size);

    // Set CURL options (example URL, replace with actual WebSocket URL if needed)
    curl_easy_setopt(curl, CURLOPT_URL, "ws://example.com");

    // Call the function under test
    res = curl_ws_recv(curl, buffer, buffer_size, &received_size, &frame);

    // Clean up
    free(buffer);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}