#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    CURL *original_handle;
    CURL *duplicate_handle;

    // Initialize a CURL session
    original_handle = curl_easy_init();
    if (!original_handle) {
        return 0;
    }

    // Set some options on the original handle to ensure it's not NULL
    curl_easy_setopt(original_handle, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(original_handle, CURLOPT_FOLLOWLOCATION, 1L);

    // Call the function-under-test
    duplicate_handle = curl_easy_duphandle(original_handle);

    // Clean up
    if (duplicate_handle) {
        curl_easy_cleanup(duplicate_handle);
    }
    curl_easy_cleanup(original_handle);

    return 0;
}