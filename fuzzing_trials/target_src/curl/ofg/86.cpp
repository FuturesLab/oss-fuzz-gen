#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    CURLU *url_handle;

    // Initialize a CURLU handle
    url_handle = curl_url();

    if (url_handle != NULL) {
        // Use the data and size in some way to manipulate the CURLU handle
        // For example, set a URL part if the size is sufficient
        if (size > 0) {
            char *url_part = (char *)malloc(size + 1);
            if (url_part != NULL) {
                memcpy(url_part, data, size);
                url_part[size] = '\0';  // Null-terminate the string

                // Set the URL part (CURLUPART_URL is used as an example)
                curl_url_set(url_handle, CURLUPART_URL, url_part, 0);

                free(url_part);
            }
        }

        // Call the function-under-test
        curl_url_cleanup(url_handle);
    }

    return 0;
}