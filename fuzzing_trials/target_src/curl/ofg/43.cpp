#include <curl/curl.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for mkstemp and close

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    curl_mime *mime;
    curl_mimepart *part;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(!curl) {
        curl_global_cleanup();
        return 0;
    }

    // Create a temporary file
    fd = mkstemp(tmpl);
    if (fd == -1) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Write data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Create a mime handle
    mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Create a mime part
    part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
    }

    // Call the function-under-test
    res = curl_mime_filedata(part, tmpl);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    remove(tmpl);

    return 0;
}