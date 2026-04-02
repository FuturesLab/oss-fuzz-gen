#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;
    char filename[256];

    if (size == 0) {
        return 0;
    }

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Initialize MIME
    mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Add a part to the MIME
    part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Copy data to filename buffer ensuring null-termination
    size_t filename_len = size < sizeof(filename) - 1 ? size : sizeof(filename) - 1;
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    // Call the function-under-test
    res = curl_mime_filename(part, filename);

    // Cleanup
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}