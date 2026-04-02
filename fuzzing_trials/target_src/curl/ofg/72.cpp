#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        return 0;
    }

    // Initialize a curl_mime structure
    curl_mime *mime = curl_mime_init(easy_handle);
    if (!mime) {
        curl_easy_cleanup(easy_handle);
        return 0;
    }

    // Call the function-under-test
    curl_mimepart *part = curl_mime_addpart(mime);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(easy_handle);

    return 0;
}