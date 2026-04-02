#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Initialize a CURL mime handle
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Initialize a CURL mime part
    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Ensure the filename is null-terminated
    char *filename = (char *)malloc(size + 1);
    if (!filename) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    CURLcode result = curl_mime_filename(part, filename);

    // Clean up
    free(filename);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}