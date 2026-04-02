#include "curl/curl.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    size_t sent_bytes = 0;

    // Initialize a CURL session
    curl = curl_easy_init();
    if(curl) {
        // Set CURL options for sending data
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

        // Perform the connection
        res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            // Attempt to send data using curl_easy_send
            res = curl_easy_send(curl, data, size, &sent_bytes);
        }

        // Cleanup CURL session
        curl_easy_cleanup(curl);
    }

    return 0;
}