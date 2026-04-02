#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    
    // Initialize a CURL session
    curl = curl_easy_init();
    if(curl) {
        // Create a temporary URL from the input data
        char url[256];
        snprintf(url, sizeof(url), "http://example.com/%.*s", (int)size, data);

        // Set the URL for the CURL session
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the request
        res = curl_easy_perform(curl);

        // Always cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}