#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Ensure C linkage for C++ compilation
extern "C" {
    #include "curl/curl.h"
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        return 0;
    }

    // Initialize a mime structure
    curl_mime *mime = curl_mime_init(easy_handle);
    if (!mime) {
        curl_easy_cleanup(easy_handle);
        return 0;
    }

    // Add a part to the mime structure
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy_handle);
        return 0;
    }

    // Ensure the data is null-terminated for the function call
    char *data_with_null = (char *)malloc(size + 1);
    if (!data_with_null) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy_handle);
        return 0;
    }
    memcpy(data_with_null, data, size);
    data_with_null[size] = '\0';

    // Call the function-under-test
    CURLcode result = curl_mime_data(part, data_with_null, CURL_ZERO_TERMINATED);

    // Clean up
    free(data_with_null);
    curl_mime_free(mime);
    curl_easy_cleanup(easy_handle);

    return 0;
}