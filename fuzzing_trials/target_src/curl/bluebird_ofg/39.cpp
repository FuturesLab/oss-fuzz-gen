#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include "curl/curl.h"
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize a CURL mime part using the curl_mime_init function
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

    // Prepare a null-terminated string from the input data for the encoder name
    char encoder_name[256];
    size_t copy_size = (size < 255) ? size : 255;
    memcpy(encoder_name, data, copy_size);
    encoder_name[copy_size] = '\0';

    // Call the function-under-test
    CURLcode result = curl_mime_encoder(part, encoder_name);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}