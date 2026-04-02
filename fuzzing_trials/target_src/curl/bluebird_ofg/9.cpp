#include "curl/curl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Initialize a curl_mimepart
    CURL *easy_handle = curl_easy_init();
    if (!easy_handle) {
        return 0;
    }
    curl_mime *mime = curl_mime_init(easy_handle);
    if (!mime) {
        curl_easy_cleanup(easy_handle);
        return 0;
    }
    curl_mimepart *part = curl_mime_addpart(mime);

    // Initialize a curl_slist
    struct curl_slist *slist = NULL;
    if (size > 0) {
        // Convert data to a null-terminated string
        char *header = (char *)malloc(size + 1);
        if (!header) {
            curl_mime_free(mime);
            curl_easy_cleanup(easy_handle);
            return 0;
        }
        memcpy(header, data, size);
        header[size] = '\0';

        // Add the header to the slist
        slist = curl_slist_append(slist, header);
        free(header);
    }

    // Use a fixed integer for the third parameter
    int take_ownership = 1;

    // Call the function-under-test
    curl_mime_headers(part, slist, take_ownership);

    // Cleanup
    curl_mime_free(mime);
    curl_easy_cleanup(easy_handle);

    return 0;
}