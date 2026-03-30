#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        return 0;
    }

    // Initialize curl_mime and curl_mimepart
    curl_mime *mime = curl_mime_init(easy_handle);
    if (!mime) {
        curl_easy_cleanup(easy_handle);
        return 0;
    }

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy_handle);
        return 0;
    }

    // Create a subpart mime object
    curl_mime *sub_mime = curl_mime_init(easy_handle);
    if (!sub_mime) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy_handle);
        return 0;
    }

    // Fuzz the function-under-test
    CURLcode result = curl_mime_subparts(part, sub_mime);

    // Clean up
    curl_mime_free(mime); // This will also free sub_mime
    curl_easy_cleanup(easy_handle);

    return 0;
}