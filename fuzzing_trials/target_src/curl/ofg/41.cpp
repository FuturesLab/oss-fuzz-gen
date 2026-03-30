#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    
    // Initialize a CURL session
    curl = curl_easy_init();
    if(curl) {
        // Convert the input data to a string URL
        // Ensure the data is null-terminated
        char *url = (char *)malloc(size + 1);
        if (url == NULL) {
            curl_easy_cleanup(curl);
            return 0;
        }
        memcpy(url, data, size);
        url[size] = '\0';

        // Set the URL that is about to receive our GET request
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Always cleanup
        curl_easy_cleanup(curl);
        free(url);
    }
    return 0;
}