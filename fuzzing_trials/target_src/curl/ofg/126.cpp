#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    CURLMcode mcode;

    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize a CURLM handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Initialize a CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        curl_global_cleanup();
        return 0;
    }

    // Set a URL for the easy handle, using data as a dummy URL
    // Ensure the data is null-terminated for safety
    char url[256];
    size_t url_length = size < 255 ? size : 255;
    memcpy(url, data, url_length);
    url[url_length] = '\0';

    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    mcode = curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the request, ignoring the result for fuzzing purposes
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Cleanup
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}