#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    char *url = (char *)malloc(size + 1);

    if (url == NULL) {
        return 0;
    }

    // Ensure the URL is null-terminated
    memcpy(url, data, size);
    url[size] = '\0';

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Set the URL from the fuzzing input
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the request, this will increase code coverage
        res = curl_easy_perform(curl);

        // Clean up
        curl_easy_cleanup(curl);
    }

    free(url);
    curl_global_cleanup();

    return 0;
}