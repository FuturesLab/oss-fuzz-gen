#include "curl/curl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    size_t bytes_sent = 0;

    // Initialize a CURL session
    curl = curl_easy_init();
    if(curl) {
        // Set the URL, for example, to a local server or a test server
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080");

        // Set the CURLOPT_CONNECT_ONLY option to 1L to tell libcurl to only connect to the server
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

        // Perform the connection
        res = curl_easy_perform(curl);

        if(res == CURLE_OK) {
            // Send data using curl_easy_send
            res = curl_easy_send(curl, data, size, &bytes_sent);

            // Check the result of the send operation
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_send() failed: %s\n", curl_easy_strerror(res));
            } else {
                printf("Sent %zu bytes\n", bytes_sent);
            }
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup the CURL session
        curl_easy_cleanup(curl);
    }

    return 0;
}