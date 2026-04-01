#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl_handle = curl_easy_init();
    if (curl_handle == NULL) {
        return 0; // Return if initialization fails
    }

    // Call the function-under-test
    curl_mime *mime = curl_mime_init(curl_handle);

    // Clean up
    if (mime != NULL) {
        curl_mime_free(mime);
    }
    curl_easy_cleanup(curl_handle);

    return 0;
}