#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    CURLINFO info;
    char *url = NULL;

    // Initialize a CURL session
    curl = curl_easy_init();
    if(curl == NULL) {
        return 0;
    }

    // Ensure the data size is sufficient for a URL
    if (size > 0) {
        // Allocate memory for the URL and copy data into it
        url = (char *)malloc(size + 1);
        if (url == NULL) {
            curl_easy_cleanup(curl);
            return 0;
        }
        memcpy(url, data, size);
        url[size] = '\0';

        // Set the URL for the CURL session
        curl_easy_setopt(curl, CURLOPT_URL, url);
    }

    // Set a valid CURLINFO option for testing
    info = CURLINFO_EFFECTIVE_URL;

    // Prepare a buffer to receive information
    char *info_data = NULL;

    // Perform the request
    res = curl_easy_perform(curl);

    // Call the function-under-test
    if(res == CURLE_OK) {
        curl_easy_getinfo(curl, info, &info_data);
    }

    // Clean up
    if (url != NULL) {
        free(url);
    }
    curl_easy_cleanup(curl);

    return 0;
}