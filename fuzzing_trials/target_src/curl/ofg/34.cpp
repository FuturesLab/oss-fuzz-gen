#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Initialize CURL
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

    // Ensure that the data is null-terminated for string operations
    char *name = new char[size + 1];
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    curl_mime_name(part, name);

    // Clean up
    delete[] name;
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}