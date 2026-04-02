#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Avoid processing empty inputs
    }

    CURL *curl;
    CURLcode res;
    size_t sent_bytes = 0;
    curl_off_t offset = 0;
    unsigned int flags = 0;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        // Set up CURL options
        curl_easy_setopt(curl, CURLOPT_URL, "ws://example.com"); // Example WebSocket URL
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L); // Prepare for WebSocket connection

        // Perform the connection
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            // Call the function-under-test with valid WebSocket context
            res = curl_ws_send(curl, data, size, &sent_bytes, offset, flags);
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}