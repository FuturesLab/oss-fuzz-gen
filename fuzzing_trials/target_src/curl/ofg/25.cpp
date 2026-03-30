#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    CURL *curl;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set options for CURL if needed
        // Use the input data as a URL to ensure the function is tested with real input
        if (size > 0) {
            char *url = (char *)malloc(size + 1);
            if (url) {
                memcpy(url, data, size);
                url[size] = '\0'; // Null-terminate the string

                curl_easy_setopt(curl, CURLOPT_URL, url);

                // Perform the request, curl_easy_perform() returns 0 on success
                CURLcode res = curl_easy_perform(curl);

                // Check for errors
                if(res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                }

                free(url);
            }
        }

        // Perform any necessary cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}