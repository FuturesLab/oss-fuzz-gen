#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  // Include this for uint8_t
#include <curl/curl.h>

extern "C" {
    // Wrap the function with extern "C" to ensure C linkage
    int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
        CURLU *url;
        CURLUcode result;
        char *url_part = NULL;

        // Initialize a CURLU handle
        url = curl_url();
        if (url == NULL) {
            return 0;
        }

        // Make sure the data is null-terminated before using it as a URL
        char *url_data = (char *)malloc(size + 1);
        if (url_data == NULL) {
            curl_url_cleanup(url);
            return 0;
        }
        memcpy(url_data, data, size);
        url_data[size] = '\0';

        // Set the URL in the CURLU handle
        result = curl_url_set(url, CURLUPART_URL, url_data, 0);
        if (result != CURLUE_OK) {
            free(url_data);
            curl_url_cleanup(url);
            return 0;
        }

        // Attempt to get various parts of the URL
        CURLUPart parts[] = {CURLUPART_SCHEME, CURLUPART_HOST, CURLUPART_PATH, CURLUPART_QUERY, CURLUPART_FRAGMENT};
        for (size_t i = 0; i < sizeof(parts) / sizeof(parts[0]); ++i) {
            result = curl_url_get(url, parts[i], &url_part, 0);
            if (result == CURLUE_OK && url_part != NULL) {
                // Normally, you'd use the url_part here
                curl_free(url_part);
            }
        }

        // Clean up
        free(url_data);
        curl_url_cleanup(url);

        return 0;
    }
}