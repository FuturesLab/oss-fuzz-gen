#include <curl/curl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    CURL *curl;
    CURLcode res;
    size_t sent = 0;
    curl_off_t offset = 0;
    unsigned int flags = 0;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // Ensure the data is not NULL and has a size
        if (data && size > 0) {
            // Call the function under test
            res = curl_ws_send(curl, data, size, &sent, offset, flags);

            // Check the result for debugging purposes (optional)
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_ws_send() failed: %s\n", curl_easy_strerror(res));
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}