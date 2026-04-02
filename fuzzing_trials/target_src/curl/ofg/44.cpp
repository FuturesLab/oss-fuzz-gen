#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    int running_handles;

    // Initialize the CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // If initialization fails, return early
    }

    // Initialize a CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0; // If initialization fails, return early
    }

    // Set a URL option for the easy handle
    // Convert the fuzz input data to a string and use it as a URL
    char url[256];
    snprintf(url, sizeof(url), "http://example.com/%.*s", (int)size, data);
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Call the function-under-test
    CURLMcode result = curl_multi_socket_all(multi_handle, &running_handles);

    // Clean up
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);

    return 0;
}