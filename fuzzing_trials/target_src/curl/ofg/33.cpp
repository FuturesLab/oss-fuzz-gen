#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a CURL easy handle
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        curl_global_cleanup();
        return 0;
    }

    // Create a mime structure
    curl_mime *mime = curl_mime_init(easy_handle);
    if (!mime) {
        curl_easy_cleanup(easy_handle);
        curl_global_cleanup();
        return 0;
    }

    // Add a mime part
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy_handle);
        curl_global_cleanup();
        return 0;
    }

    // Create a curl_slist structure for headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: text/plain");
    if (!headers) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy_handle);
        curl_global_cleanup();
        return 0;
    }

    // Use the data to determine the 'take_ownership' parameter
    int take_ownership = (size > 0) ? data[0] % 2 : 0;

    // Call the function-under-test
    CURLcode result = curl_mime_headers(part, headers, take_ownership);

    // Clean up
    curl_slist_free_all(headers);
    curl_mime_free(mime);
    curl_easy_cleanup(easy_handle);
    curl_global_cleanup();

    return 0;
}