#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    size_t sent_bytes = 0;

    // Initialize curl
    curl = curl_easy_init();
    if (curl) {
        // Set a dummy URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

        // Set the connection to use a dummy socket
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

        // Perform the connection
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            // Attempt to send the fuzz data
            res = curl_easy_send(curl, data, size, &sent_bytes);
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}