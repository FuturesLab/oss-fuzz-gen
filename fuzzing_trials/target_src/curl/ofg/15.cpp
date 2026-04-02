#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    CURLU *urlp = curl_url();
    if (urlp == NULL) {
        return 0;
    }

    // Attempt to set the URL from the input data
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        curl_url_cleanup(urlp);
        return 0;
    }

    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the URL string

    // Set the URL in the CURLU object
    curl_url_set(urlp, CURLUPART_URL, url, 0);

    // Clean up
    curl_url_cleanup(urlp);
    free(url);

    return 0;
}