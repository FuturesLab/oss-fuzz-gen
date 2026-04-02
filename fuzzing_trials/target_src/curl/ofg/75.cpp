#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    if (multi_handle == NULL) {
        return 0; // Initialization failed, exit early.
    }

    // Create a new easy handle
    CURL *easy_handle = curl_easy_init();
    if (easy_handle == NULL) {
        curl_multi_cleanup(multi_handle);
        return 0; // Initialization failed, exit early.
    }

    // Convert the input data to a string URL
    char url[256] = {0}; // Ensure the URL buffer is large enough
    snprintf(url, sizeof(url), "http://example.com/%.*s", (int)size, data);

    // Set options for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the multi handle operation
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Clean up the easy handle
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);

    // Clean up the multi handle
    curl_multi_cleanup(multi_handle);

    return 0;
}