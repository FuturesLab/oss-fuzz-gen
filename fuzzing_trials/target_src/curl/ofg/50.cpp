#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return 0;
    }

    // Initialize a curl_mime structure using the curl handle
    curl_mime *mime = curl_mime_init(curl);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}