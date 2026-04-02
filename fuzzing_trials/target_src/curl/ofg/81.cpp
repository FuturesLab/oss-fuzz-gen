#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set the URL to a valid endpoint, e.g., a local server
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080");

        // Set the data to be sent as POST fields
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, size);

        // Call the function-under-test
        res = curl_easy_perform(curl);

        // Check the result
        if(res != CURLE_OK) {
            // Handle error if needed
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Clean up CURL global environment
    curl_global_cleanup();

    return 0;
}