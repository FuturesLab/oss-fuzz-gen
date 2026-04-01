#include "curl/curl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a new mime structure
    curl_mime *mime = curl_mime_init(NULL);
    if (!mime) {
        curl_global_cleanup();
        return 0;
    }

    // Create a new mime part
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_global_cleanup();
        return 0;
    }

    // Ensure that the data is null-terminated for use as a string
    char *encoder = (char *)malloc(size + 1);
    if (!encoder) {
        curl_mime_free(mime);
        curl_global_cleanup();
        return 0;
    }
    memcpy(encoder, data, size);
    encoder[size] = '\0';

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function curl_mime_encoder with curl_mime_filedata
    CURLcode result = curl_mime_filedata(part, encoder);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Clean up
    free(encoder);
    curl_mime_free(mime);
    curl_global_cleanup();

    return 0;
}