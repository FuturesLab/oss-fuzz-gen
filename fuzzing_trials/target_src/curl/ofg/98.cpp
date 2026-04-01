#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Initialize a CURL handle
    CURL *curl_handle = curl_easy_init();
    
    // Ensure the CURL handle is not NULL
    if (curl_handle == NULL) {
        return 0;
    }
    
    // Call the function-under-test
    curl_easy_reset(curl_handle);
    
    // Cleanup the CURL handle
    curl_easy_cleanup(curl_handle);
    
    return 0;
}