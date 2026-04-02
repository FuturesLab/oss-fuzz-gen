#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    CURLcode curl_mime_data_cb(curl_mimepart *, curl_off_t, curl_read_callback, curl_seek_callback, curl_free_callback, void *);
}

// Dummy read callback function
size_t read_callback_30(char *buffer, size_t size, size_t nitems, void *instream) {
    // Simply copy data from instream to buffer
    size_t total_size = size * nitems;
    memcpy(buffer, instream, total_size);
    return total_size;
}

// Dummy seek callback function
int seek_callback_30(void *instream, curl_off_t offset, int origin) {
    // Dummy seek implementation
    return CURL_SEEKFUNC_OK;
}

// Dummy free callback function
void free_callback_30(void *ptr) {
    // Dummy free implementation
    free(ptr);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    curl_mime *mime = curl_mime_init(curl);
    if (!mime) {
        curl_easy_cleanup(curl);
        return 0;
    }

    curl_mimepart *part = curl_mime_addpart(mime);
    if (!part) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Allocate memory for the data to be used in callbacks
    void *instream = malloc(size);
    if (!instream) {
        curl_mime_free(mime);
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(instream, data, size);

    // Use the function-under-test
    CURLcode result = curl_mime_data_cb(part, (curl_off_t)size, read_callback_30, seek_callback_30, free_callback_30, instream);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}