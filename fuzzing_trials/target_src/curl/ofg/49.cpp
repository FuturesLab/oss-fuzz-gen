#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Initialize a CURLSH handle
    CURLSH *share_handle = curl_share_init();
    
    if (share_handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Use fuzzing input to set options dynamically
    if (size > 0) {
        // Use the first byte of data to decide which CURLSHOPT_* option to use
        int option = data[0] % 3; // We have three options to choose from
        switch (option) {
            case 0:
                curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
                break;
            case 1:
                curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
                break;
            case 2:
                curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
                break;
            default:
                break;
        }
    }

    // Call the function-under-test
    CURLSHcode result = curl_share_cleanup(share_handle);

    // The result can be checked if needed, but for fuzzing, we mainly focus on calling the function
    (void)result; // Suppress unused variable warning

    return 0;
}