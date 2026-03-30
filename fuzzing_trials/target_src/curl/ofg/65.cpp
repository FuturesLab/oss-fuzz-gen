#include <curl/curl.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for strlen and memcpy

extern "C" {

static size_t read_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
    // Implement a simple read callback
    const char *data = static_cast<const char *>(userdata);
    size_t data_len = strlen(data);
    size_t total_size = size * nitems;

    if (total_size < data_len) {
        memcpy(buffer, data, total_size);
        return total_size;
    } else {
        memcpy(buffer, data, data_len);
        return data_len;
    }
}

static int seek_callback(void *instream, curl_off_t offset, int origin) {
    // Simple seek callback that does nothing
    return CURL_SEEKFUNC_OK;
}

static void free_callback(void *ptr) {
    // Free callback does nothing in this example
}

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    curl_mime *mime = curl_mime_init(curl);
    curl_mimepart *part = curl_mime_addpart(mime);

    // Use the input data as the user data for the read callback
    const char *user_data = reinterpret_cast<const char *>(data);

    // Call the function-under-test
    CURLcode result = curl_mime_data_cb(part, (curl_off_t)size, read_callback, seek_callback, free_callback, (void *)user_data);

    // Clean up
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    return 0;
}

}