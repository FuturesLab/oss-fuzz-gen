#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    size_t sent = 0;
    curl_off_t offset = 0;
    unsigned int flags = 0;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Set a dummy URL (required by CURL)
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

    // Set up a WebSocket connection
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Ensure data is not null and has a minimum size
    if (data == NULL || size == 0) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Fuzz the curl_ws_send function
    res = curl_ws_send(curl, (const void *)data, size, &sent, offset, flags);

    // Check the result of the send operation
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_ws_send failed: %s\n", curl_easy_strerror(res));
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}