#include <curl/curl.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *handle = curl_easy_init();
    if (handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Set some options on the handle to ensure it's not NULL
    curl_easy_setopt(handle, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);

    // Call the function-under-test
    CURL *dup_handle = curl_easy_duphandle(handle);

    // Clean up the duplicated handle
    if (dup_handle != NULL) {
        curl_easy_cleanup(dup_handle);
    }

    // Clean up the original handle
    curl_easy_cleanup(handle);

    return 0;
}