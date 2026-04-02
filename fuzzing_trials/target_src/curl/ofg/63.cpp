#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    CURLM *multi_handle;
    CURL *easy_handle;
    int still_running; // to check if there are still transfers running

    // Initialize CURL multi handle
    multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Initialize CURL easy handle
    easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Convert the input data to a string and set it as a URL
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_easy_cleanup(easy_handle);
        curl_multi_cleanup(multi_handle);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the URL string

    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, NULL); // Discard output

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, easy_handle);

    // Perform the request
    curl_multi_perform(multi_handle, &still_running);

    // Wait for transfers to complete
    while (still_running) {
        int numfds;
        CURLMcode mc = curl_multi_wait(multi_handle, NULL, 0, 1000, &numfds);
        if (mc != CURLM_OK) {
            break;
        }
        curl_multi_perform(multi_handle, &still_running);
    }

    // Cleanup
    curl_multi_remove_handle(multi_handle, easy_handle);
    curl_easy_cleanup(easy_handle);
    curl_multi_cleanup(multi_handle);
    free(url);

    return 0;
}