#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return 0;
    }

    // Initialize a mime structure
    curl_mime *mime = curl_mime_init(curl);
    if (mime == NULL) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Initialize a mime part
    curl_mimepart *part = curl_mime_addpart(mime);
    if (part == NULL) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Create another mime structure to be used as subparts
    curl_mime *subparts = curl_mime_init(curl);
    if (subparts == NULL) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Call the function-under-test
    CURLcode result = curl_mime_subparts(part, subparts);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}