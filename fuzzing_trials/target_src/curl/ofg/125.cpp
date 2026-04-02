#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For mkstemp, write, close, unlink
#include <fcntl.h>   // For open

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Initialize a MIME structure
    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Add a part to the MIME structure
    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Create a temporary file to store the fuzz input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Write the fuzz input to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }
    close(fd);

    // Call the function-under-test
    CURLcode result = curl_mime_filedata(part, tmpl);

    // Clean up
    unlink(tmpl);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}