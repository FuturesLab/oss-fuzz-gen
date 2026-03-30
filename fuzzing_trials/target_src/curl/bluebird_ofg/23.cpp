#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>

extern "C" {

// Callback function for CURLOPT_WRITEFUNCTION
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    // For fuzzing purposes, the callback can just return the number of bytes processed
    return size * nmemb;
}

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    CURL *curl_handle;
    CURLcode result;
    void *user_data = (void *)data; // Use the fuzzing input data as user data

    // Initialize a CURL easy session
    curl_handle = curl_easy_init();
    if (!curl_handle) {
        return 0;
    }

    // Set the URL option, assuming data contains a valid URL
    result = curl_easy_setopt(curl_handle, CURLOPT_URL, "http://example.com");

    // Set the write callback function
    result = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);

    // Set the user data for the callback
    result = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, user_data);

    // Perform the request, result will get the return code
    result = curl_easy_perform(curl_handle);

    // Cleanup CURL easy session
    curl_easy_cleanup(curl_handle);

    return 0;
}

}