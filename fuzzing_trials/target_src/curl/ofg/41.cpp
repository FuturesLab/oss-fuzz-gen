#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    CURL *handle = curl_easy_init();
    CURL *duphandle = NULL;

    if (handle != NULL) {
        // Setting some options to ensure the handle is not NULL and is usable
        curl_easy_setopt(handle, CURLOPT_URL, "http://example.com");
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);

        // Now, fuzz the curl_easy_duphandle function
        duphandle = curl_easy_duphandle(handle);

        // Cleanup
        if (duphandle != NULL) {
            curl_easy_cleanup(duphandle);
        }
        curl_easy_cleanup(handle);
    }

    return 0;
}