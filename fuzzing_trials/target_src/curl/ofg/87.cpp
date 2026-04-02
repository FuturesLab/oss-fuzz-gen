#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl_handle = curl_easy_init();
    
    if (curl_handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Use the data to set some options if possible
    if (size > 0) {
        // Example: Set a URL option if the data size is sufficient
        char url[256];
        size_t url_length = size < 255 ? size : 255; // Ensure no buffer overflow
        memcpy(url, data, url_length);
        url[url_length] = '\0'; // Null-terminate the URL string

        // Set the URL option (this is just an example, URL might not be valid)
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    }

    // Perform the operation to ensure the function-under-test is invoked
    CURLcode res = curl_easy_perform(curl_handle);

    // Check for errors
    if(res != CURLE_OK) {
        // Handle the error if needed
    }

    // Clean up the CURL handle
    curl_easy_cleanup(curl_handle);

    return 0;
}