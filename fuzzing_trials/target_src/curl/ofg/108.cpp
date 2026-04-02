#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Initialize curl_mime and curl_mimepart
    curl_mime *mime = curl_mime_init(curl);
    curl_mimepart *part = curl_mime_addpart(mime);

    // Ensure the data is not empty to avoid unnecessary calls
    if (size > 0) {
        // Create a new mime structure to use as subparts
        curl_mime *subparts = curl_mime_init(curl);
        if (subparts) {
            // Add a simple part to the subparts for testing
            curl_mimepart *subpart = curl_mime_addpart(subparts);
            curl_mime_data(subpart, (const char *)data, CURL_ZERO_TERMINATED);

            // Call the function-under-test with initialized parameters
            curl_mime_subparts(part, subparts);

            // Cleanup subparts
            curl_mime_free(subparts);
        }
    }

    // Cleanup
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}