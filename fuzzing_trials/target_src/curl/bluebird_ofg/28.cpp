#include <cstddef>
#include <cstdint>
#include "curl/curl.h"
#include <cstring>
#include <cstdlib> // Include for malloc and free

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Create a mime structure
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

    // Ensure the data is null-terminated for safety
    char *data_copy = static_cast<char *>(malloc(size + 1));
    if (!data_copy) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Call the function-under-test
    CURLcode result = curl_mime_data(part, data_copy, CURL_ZERO_TERMINATED);

    // Clean up
    free(data_copy);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}