#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURLMcode result;
    CURL *easy_handle;
    
    // Initialize a CURLM handle
    multi_handle = curl_multi_init();
    if (multi_handle == NULL) {
        return 0; // If initialization failed, return early
    }

    // Initialize a CURL easy handle
    easy_handle = curl_easy_init();
    if (easy_handle == NULL) {
        curl_multi_cleanup(multi_handle);
        return 0; // If initialization failed, return early
    }

    // Set some options for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE, size);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Call the function-under-test
    result = curl_multi_wakeup(multi_handle);

    // Perform the request
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Clean up the easy handle
    curl_easy_cleanup(easy_handle);

    // Clean up the CURLM handle
    curl_multi_cleanup(multi_handle);

    return 0;
}