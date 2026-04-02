#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl_handle = curl_easy_init();
    if (curl_handle == NULL) {
        return 0; // If initialization fails, return early
    }

    // Convert the input data to a URL string
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_easy_cleanup(curl_handle);
        return 0; // If memory allocation fails, return early
    }
    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the string

    // Set the URL for the CURL handle
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    // Perform the request, ignore the result for fuzzing purposes
    curl_easy_perform(curl_handle);

    // Clean up
    free(url);
    curl_easy_cleanup(curl_handle);

    return 0;
}