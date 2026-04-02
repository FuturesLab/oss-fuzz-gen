#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Call the function-under-test
    CURLU *url = curl_url();

    // Clean up if the function returns a non-NULL pointer
    if (url != NULL) {
        curl_url_cleanup(url);
    }

    return 0;
}