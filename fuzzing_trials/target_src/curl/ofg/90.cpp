#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    CURL *curl_handle;

    // Initialize a CURL session
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_handle = curl_easy_init();

    if(curl_handle) {
        // Set some options for the CURL session
        // Here we use the data as a URL, but ensure it's null-terminated
        char url[256];
        size_t url_length = size < 255 ? size : 255;
        memcpy(url, data, url_length);
        url[url_length] = '\0';

        // Set the URL option
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);

        // Perform the upkeep operation
        curl_easy_upkeep(curl_handle);

        // Cleanup the CURL session
        curl_easy_cleanup(curl_handle);
    }

    // Cleanup global CURL resources
    curl_global_cleanup();

    return 0;
}