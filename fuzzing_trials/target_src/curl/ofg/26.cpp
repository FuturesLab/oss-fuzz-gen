#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    struct curl_header * curl_easy_nextheader(CURL *, unsigned int, int, struct curl_header *);
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    CURL *curl;
    struct curl_header *header = NULL;
    unsigned int origin = 0; // Example value, can be varied
    int partial = 0; // Example value, can be varied

    // Initialize a CURL easy handle
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Convert the fuzz data into a string URL
    char *url = (char *)malloc(size + 1);
    if (!url) {
        curl_easy_cleanup(curl);
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Set a URL for the CURL handle
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Perform a request to ensure the function under test is invoked
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        // If the request fails, we still want to invoke the function under test
        header = curl_easy_nextheader(curl, origin, partial, header);
    } else {
        // If the request succeeds, also invoke the function under test
        header = curl_easy_nextheader(curl, origin, partial, header);
    }

    // Cleanup
    free(url);
    curl_easy_cleanup(curl);

    return 0;
}