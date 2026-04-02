#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    CURLU *url_handle = curl_url();  // Initialize a CURLU handle
    if (url_handle == NULL) {
        return 0;  // If initialization fails, return
    }

    // Create a null-terminated string from the input data
    char *url_string = (char *)malloc(size + 1);
    if (url_string == NULL) {
        curl_url_cleanup(url_handle);
        return 0;
    }
    memcpy(url_string, data, size);
    url_string[size] = '\0';

    // Set the URL in the CURLU handle
    CURLUcode set_result = curl_url_set(url_handle, CURLUPART_URL, url_string, 0);
    free(url_string);

    if (set_result == CURLUE_OK) {
        // Duplicate the CURLU handle
        CURLU *dup_handle = curl_url_dup(url_handle);
        if (dup_handle != NULL) {
            // Clean up the duplicated handle
            curl_url_cleanup(dup_handle);
        }
    }

    // Clean up the original handle
    curl_url_cleanup(url_handle);

    return 0;
}