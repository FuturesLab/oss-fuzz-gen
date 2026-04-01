#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    long timeout;

    // Initialize the CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // If initialization fails, return immediately
    }

    // Create a new easy handle
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Convert the input data to a string URL if possible
    char url[256];
    snprintf(url, sizeof(url), "http://%.*s", (int)size, data);

    // Set the URL for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Call the function-under-test
    CURLMcode result = curl_multi_timeout(multi_handle, &timeout);

    // Perform the multi handle actions
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Clean up the CURL handles
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}