#include <cstdint>
#include <cstddef>
#include "curl/curl.h"
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Create a mime handle
    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Create a mime part
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Ensure the input data is null-terminated for use as a string
    char *name = new char[size + 1];
    memcpy(name, data, size);
    name[size] = '\0';

    // Fuzz the function
    curl_mime_name(part, name);

    // Clean up
    delete[] name;
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}