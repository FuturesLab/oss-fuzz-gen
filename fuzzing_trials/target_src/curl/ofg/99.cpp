#include <curl/curl.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Initialize a CURL pointer
    CURL *curl = curl_easy_init();
    
    if (curl) {
        // Call the function-under-test
        curl_easy_reset(curl);
        
        // Cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}