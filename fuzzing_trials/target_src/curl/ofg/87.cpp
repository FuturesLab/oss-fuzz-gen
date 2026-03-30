#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    CURLU *url_handle = curl_url();  // Initialize a CURLU handle

    // Ensure that the CURLU handle is not NULL
    if (url_handle == NULL) {
        return 0;
    }

    // Use the input data to set a URL in the CURLU handle
    // Ensure that the data is null-terminated for safety
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_url_cleanup(url_handle);
        return 0;
    }

    memcpy(url, data, size);
    url[size] = '\0';  // Null-terminate the string

    // Set the URL in the CURLU handle
    curl_url_set(url_handle, CURLUPART_URL, url, 0);

    // Clean up
    free(url);
    curl_url_cleanup(url_handle);

    return 0;
}