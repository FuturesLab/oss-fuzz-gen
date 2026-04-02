#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" const struct curl_ws_frame *curl_ws_meta(CURL *);

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    // Set some options to ensure the CURL handle is valid and initialized
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Call the function-under-test
    const struct curl_ws_frame *ws_frame = curl_ws_meta(curl);

    // Normally, you would use ws_frame here, but since this is a fuzzing harness,
    // we are mainly interested in calling the function to check for memory issues.

    // Clean up CURL handle
    curl_easy_cleanup(curl);

    return 0;
}