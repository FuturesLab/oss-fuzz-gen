#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        // Create a mime handle
        mime = curl_mime_init(curl);

        // Add a part to the mime handle
        part = curl_mime_addpart(mime);

        // Ensure the data is null-terminated for safety
        char *data_copy = (char *)malloc(size + 1);
        memcpy(data_copy, data, size);
        data_copy[size] = '\0';

        // Call the function-under-test
        res = curl_mime_data(part, data_copy, size);

        // Clean up
        free(data_copy);
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}