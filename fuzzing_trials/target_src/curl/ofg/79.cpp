#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Initialize libcurl
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        return 0;
    }

    // Call the function-under-test
    curl_global_cleanup();

    return 0;
}