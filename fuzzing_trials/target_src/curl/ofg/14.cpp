#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a new mime structure
    CURL *easy = curl_easy_init();
    if (!easy) {
        curl_global_cleanup();
        return 0;
    }

    curl_mime *mime = curl_mime_init(easy);
    if (!mime) {
        curl_easy_cleanup(easy);
        curl_global_cleanup();
        return 0;
    }

    // Create a new mime part
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy);
        curl_global_cleanup();
        return 0;
    }

    // Ensure the input data is null-terminated for use as a string
    char *filename = new char[size + 1];
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    curl_mime_filename(part, filename);

    // Clean up
    delete[] filename;
    curl_mime_free(mime);
    curl_easy_cleanup(easy);
    curl_global_cleanup();

    return 0;
}