#include <cstddef>
#include <cstdint>
#include <cstring>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Initialize the CURL library
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a CURL mime handle
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Create a mime part
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

    // Ensure the data is null-terminated for string safety
    char *encoder = nullptr;
    if (size > 0) {
        encoder = new char[size + 1];
        memcpy(encoder, data, size);
        encoder[size] = '\0';
    } else {
        encoder = new char[1];
        encoder[0] = '\0';
    }

    // Call the function-under-test
    CURLcode result = curl_mime_encoder(part, encoder);

    // Clean up
    delete[] encoder;
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}