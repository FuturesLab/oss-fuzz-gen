#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Call the function-under-test
    CURLU *url_handle = curl_url();

    // Check if the URL handle was created successfully
    if (url_handle != NULL) {
        // Ensure the input data is null-terminated to be used as a string
        char *url = (char *)malloc(size + 1);
        if (url != NULL) {
            memcpy(url, data, size);
            url[size] = '\0';

            // Set the URL using the provided data
            curl_url_set(url_handle, CURLUPART_URL, url, 0);

            // Clean up the allocated URL string
            free(url);
        }

        // Clean up the URL handle
        curl_url_cleanup(url_handle);
    }

    return 0;
}