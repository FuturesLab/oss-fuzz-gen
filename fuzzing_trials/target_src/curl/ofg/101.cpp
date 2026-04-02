#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl = curl_easy_init();

    // Ensure the CURL handle is initialized
    if (curl == NULL) {
        return 0; // Exit if initialization failed
    }

    // Convert the input data to a string
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_easy_cleanup(curl);
        return 0; // Exit if memory allocation failed
    }
    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the string

    // Set the URL option with the fuzzing input
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Perform a request (this will not actually send a request due to the nature of fuzzing)
    curl_easy_perform(curl);

    // Cleanup
    free(url);
    curl_easy_cleanup(curl);

    return 0;
}