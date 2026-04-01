#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "curl/curl.h"

extern "C" {
    // Hypothetical function under test
    CURLcode curl_easy_setopt(CURL *handle, CURLoption option, ...);
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Exit if input size is too small to be meaningful
    }

    // Ensure the input data is null-terminated to safely use it as a string
    char *ptr = static_cast<char*>(malloc(size + 1));
    if (ptr == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the allocated memory
    memcpy(ptr, data, size);
    ptr[size] = '\0'; // Null-terminate the string

    // Initialize a CURL handle
    CURL *curl = curl_easy_init();
    if(curl) {
        // Use the input data in a call to a function under test
        // Set URL option
        CURLcode res = curl_easy_setopt(curl, CURLOPT_URL, ptr);
        
        // Check if setting the URL was successful
        if (res == CURLE_OK) {
            // Set additional options to increase code coverage
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

            // Perform the request to increase code coverage
            curl_easy_perform(curl);
        }

        // Clean up the CURL handle
        curl_easy_cleanup(curl);
    }

    // Free the allocated memory
    free(ptr);

    // Return 0 to indicate successful execution
    return 0;
}