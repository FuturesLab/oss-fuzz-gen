#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Set some basic options to ensure the CURL handle is valid
    // Use data to set a URL, but ensure it's null-terminated
    char url[256];
    size_t url_size = (size < 255) ? size : 255;
    memcpy(url, data, url_size);
    url[url_size] = '\0'; // Ensure null-termination

    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Perform the upkeep operation
    CURLcode res = curl_easy_upkeep(curl);

    // Cleanup
    curl_easy_cleanup(curl);

    return 0;
}