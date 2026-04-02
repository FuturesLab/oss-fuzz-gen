#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl_handle = curl_easy_init();
    
    // Ensure the CURL handle is not NULL
    if (curl_handle == NULL) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_easy_cleanup(curl_handle);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set the URL option with the fuzzed input
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    // Perform the request
    curl_easy_perform(curl_handle);

    // Clean up
    curl_easy_cleanup(curl_handle);
    free(url);

    return 0;
}