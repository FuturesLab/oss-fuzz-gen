#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    CURLU *url;
    CURLU *dup_url;
    CURLUcode result;
    
    // Initialize a CURLU handle
    url = curl_url();
    if (!url) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *url_string = (char *)malloc(size + 1);
    if (!url_string) {
        curl_url_cleanup(url);
        return 0;
    }
    memcpy(url_string, data, size);
    url_string[size] = '\0';

    // Set the URL in the CURLU handle
    result = curl_url_set(url, CURLUPART_URL, url_string, 0);
    free(url_string);

    if (result == CURLUE_OK) {
        // Duplicate the CURLU handle
        dup_url = curl_url_dup(url);
        if (dup_url) {
            // Cleanup the duplicated URL
            curl_url_cleanup(dup_url);
        }
    }

    // Cleanup the original URL
    curl_url_cleanup(url);

    return 0;
}