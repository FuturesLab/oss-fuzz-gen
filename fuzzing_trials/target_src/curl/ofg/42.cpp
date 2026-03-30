#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For mkstemp and close

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Create a temporary file to hold the fuzz data
    fd = mkstemp(tmpl);
    if (fd == -1) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Create a mime structure and add a part
    mime = curl_mime_init(curl);
    part = curl_mime_addpart(mime);

    // Call the function-under-test with the file path
    res = curl_mime_filedata(part, tmpl);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    // Remove the temporary file
    remove(tmpl);

    return 0;
}