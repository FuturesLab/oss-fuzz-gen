#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Ensure C linkage for the fuzz target function
extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    char url[256] = "http://example.com";
    long response_code;

    // Initialize CURL
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Set a URL
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return 0;
    }

    // Fuzz CURLINFO parameter
    CURLINFO info;
    if (size > 0) {
        info = static_cast<CURLINFO>(data[0] % CURLINFO_END);
    } else {
        info = CURLINFO_RESPONSE_CODE;
    }

    // Call the function-under-test
    if (info == CURLINFO_RESPONSE_CODE) {
        res = curl_easy_getinfo(curl, info, &response_code);
    }

    // Cleanup
    curl_easy_cleanup(curl);

    return 0;
}