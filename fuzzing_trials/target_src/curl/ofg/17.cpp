#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;

    // Initialize a CURL session
    curl = curl_easy_init();
    if(curl) {
        // Set the URL option for the CURL session
        // Convert the input data to a string URL, making sure it's null-terminated
        char *url = (char *)malloc(size + 1);
        if (url != NULL) {
            memcpy(url, data, size);
            url[size] = '\0'; // Null-terminate the string

            // Set the URL for the CURL session
            curl_easy_setopt(curl, CURLOPT_URL, url);

            // Perform the request
            res = curl_easy_perform(curl);

            // Clean up
            free(url);
        }

        // Always cleanup the CURL session
        curl_easy_cleanup(curl);
    }

    return 0;
}