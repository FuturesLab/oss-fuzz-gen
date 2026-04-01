#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    int running_handles;
    CURLMcode result;

    // Initialize the CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0; // If initialization fails, exit early
    }

    // Initialize the CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0; // If initialization fails, exit early
    }

    // Convert the input data to a null-terminated string for URL
    char *url = (char *)malloc(size + 1);
    if (!url) {
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set the URL for the CURL easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Ensure the `running_handles` is not NULL and has a valid initial value
    running_handles = 0;

    // Call the function-under-test
    result = curl_multi_socket_all(multi_handle, &running_handles);

    // Clean up the CURL easy handle
    curl_easy_cleanup(easy_handle);

    // Clean up the CURL multi handle
    curl_multi_cleanup(multi_handle);

    // Free the allocated URL string
    free(url);

    return 0;
}