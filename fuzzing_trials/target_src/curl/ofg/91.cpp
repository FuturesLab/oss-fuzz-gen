#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Convert the input data into a null-terminated string for URL use
    char *url = (char *)malloc(size + 1);
    if (!url) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set the URL from the fuzzing input
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Perform the request, this is the function under test
    CURLcode res = curl_easy_perform(curl);

    // Clean up
    free(url);
    curl_easy_cleanup(curl);

    return 0;
}