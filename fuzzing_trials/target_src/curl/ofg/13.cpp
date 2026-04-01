#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize a curl_mimepart structure
    CURL *easy = curl_easy_init();
    if (!easy) {
        return 0;
    }

    curl_mime *mime = curl_mime_init(easy);
    if (!mime) {
        curl_easy_cleanup(easy);
        return 0;
    }

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(easy);
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *filename = new char[size + 1];
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    curl_mime_filename(part, filename);

    // Clean up
    delete[] filename;
    curl_mime_free(mime);
    curl_easy_cleanup(easy);

    return 0;
}