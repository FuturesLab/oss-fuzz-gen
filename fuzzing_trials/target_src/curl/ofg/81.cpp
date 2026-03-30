#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;
    struct curl_slist *slist = NULL;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Initialize mime
    mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Initialize mime part
    part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Add some headers to slist
    slist = curl_slist_append(slist, "Content-Type: text/plain");
    slist = curl_slist_append(slist, "X-Custom-Header: Fuzzing");

    // Fuzz the function-under-test
    int take_ownership = size % 2; // Use size to decide ownership
    res = curl_mime_headers(part, slist, take_ownership);

    // Clean up
    if (!take_ownership) {
        curl_slist_free_all(slist);
    }
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}