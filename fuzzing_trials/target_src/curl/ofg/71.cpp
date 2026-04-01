#include <curl/curl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Return if input size is zero
    }

    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0; // Return if CURL initialization fails
    }

    // Set CURL options for WebSocket connection
    curl_easy_setopt(curl, CURLOPT_URL, "ws://example.com"); // Example WebSocket URL
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

    // Perform the connection
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return 0; // Return if connection fails
    }

    // Allocate buffer for receiving data
    void *recv_buffer = malloc(size);
    if (!recv_buffer) {
        curl_easy_cleanup(curl);
        return 0; // Return if memory allocation fails
    }

    // Copy data into the receive buffer
    memcpy(recv_buffer, data, size);

    // Initialize variables for curl_ws_recv
    size_t received_size = 0;
    const struct curl_ws_frame *frame = NULL;

    // Call the function-under-test
    CURLcode result = curl_ws_recv(curl, recv_buffer, size, &received_size, &frame);

    // Check the result to ensure the function was invoked correctly
    if (result == CURLE_OK) {
        // Optionally, process the received frame
        // For example, printing or logging the frame details for debugging
    }

    // Cleanup
    free(recv_buffer);
    curl_easy_cleanup(curl);

    return 0;
}