#include <cstddef>
#include <cstdint>
#include <curl/curl.h>
#include <cstring>
#include <cstdlib> // Include for malloc and free

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a new mime structure
    CURL *curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Create a new mime part
    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *name = (char *)malloc(size + 1);
    if (!name) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    CURLcode result = curl_mime_name(part, name);

    // Clean up
    free(name);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}