#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    size_t received_bytes = 0;
    void *buffer;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set a dummy URL, as we are not actually performing a real transfer
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

        // Allocate a buffer to receive data
        buffer = malloc(size);
        if (buffer == NULL) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 0;
        }

        // Copy data to buffer
        memcpy(buffer, data, size);

        // Call the function-under-test
        res = curl_easy_recv(curl, buffer, size, &received_bytes);

        // Clean up
        free(buffer);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}