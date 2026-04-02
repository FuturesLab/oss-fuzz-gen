#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Create a temporary file to write fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Write data to the temporary file
    write(fd, data, size);
    close(fd);

    // Initialize MIME
    mime = curl_mime_init(curl);
    if (!mime) {
        unlink(tmpl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Add a part to the MIME structure
    part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        unlink(tmpl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Call the function-under-test
    res = curl_mime_filedata(part, tmpl);

    // Clean up
    curl_mime_free(mime);
    unlink(tmpl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}