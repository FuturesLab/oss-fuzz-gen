#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Initialize the CURL multi handle
    CURLM *multi_handle = curl_multi_init();
    if (multi_handle == NULL) {
        return 0;
    }

    // Initialize a CURL easy handle
    CURL *easy_handle = curl_easy_init();
    if (easy_handle == NULL) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Create a null-terminated string from the input data
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set the URL option for the easy handle
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the request
    int still_running;
    curl_multi_perform(multi_handle, &still_running);

    // Cleanup
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    free(url);

    return 0;
}