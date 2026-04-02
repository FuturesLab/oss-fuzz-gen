#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Initialize CURLSH handle
    CURLSH *share_handle = curl_share_init();
    if (share_handle == NULL) {
        return 0; // Return if initialization fails
    }

    // Call the function-under-test
    CURLSHcode result = curl_share_cleanup(share_handle);

    // Check the result (optional, as we are mainly interested in calling the function)
    if (result != CURLSHE_OK) {
        // Handle error (optional)
    }

    return 0;
}