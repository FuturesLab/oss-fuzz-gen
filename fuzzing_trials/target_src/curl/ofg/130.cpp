#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Initialize a CURL object
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

    // Add a part to the mime structure
    curl_mimepart *part = curl_mime_addpart(mime);
    if (part) {
        // Set some data for the part, using the input data
        curl_mime_data(part, reinterpret_cast<const char*>(data), size);
    }

    // Free the mime structure
    curl_mime_free(mime);

    // Cleanup CURL
    curl_easy_cleanup(curl);

    return 0;
}