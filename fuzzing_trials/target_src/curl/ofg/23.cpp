#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include <curl/curl.h> // Ensure C linkage for the curl library
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (!curl || size == 0) {
        return 0;
    }

    // Initialize a curl_mime structure
    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Create a new mime part
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Ensure the data is null-terminated for safe string operations
    char *mime_type = (char *)malloc(size + 1);
    if (!mime_type) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(mime_type, data, size);
    mime_type[size] = '\0';

    // Call the function-under-test
    curl_mime_type(part, mime_type);

    // Clean up
    free(mime_type);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}