#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    CURL *curl;
    void *buffer;
    size_t buffer_size;
    size_t received_size;
    const struct curl_ws_frame *frame;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Allocate buffer and ensure it is not NULL
    buffer_size = size > 0 ? size : 1; // Ensure buffer size is at least 1
    buffer = malloc(buffer_size);
    if (!buffer) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Copy data into the buffer
    memcpy(buffer, data, size);

    // Call the function under test
    // Assuming curl_ws_recv is a valid function in your version of libcurl
    curl_ws_recv(curl, buffer, buffer_size, &received_size, &frame);

    // Cleanup
    free(buffer);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}