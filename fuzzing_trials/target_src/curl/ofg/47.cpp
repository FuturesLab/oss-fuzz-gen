#include <cstdint>
#include <cstddef>
#include <curl/curl.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Initialize curl_mimepart
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }
    
    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }
    
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Ensure data is null-terminated for use as a C-string
    char *mime_type = new char[size + 1];
    memcpy(mime_type, data, size);
    mime_type[size] = '\0';

    // Call the function-under-test
    curl_mime_type(part, mime_type);

    // Clean up
    delete[] mime_type;
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}