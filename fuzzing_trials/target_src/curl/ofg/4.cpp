#include <stdint.h>
#include <stdlib.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize CURLSH pointer
    CURLSH *share_handle = curl_share_init();
    if (share_handle == NULL) {
        return 0; // If initialization fails, exit the fuzzing iteration
    }

    // Use input data to set options on the share handle
    if (size > 0) {
        CURLSHcode res;

        // Use the first byte of data to determine which option to set
        switch (data[0] % 3) {
            case 0:
                res = curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
                break;
            case 1:
                res = curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
                break;
            case 2:
                res = curl_share_setopt(share_handle, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
                break;
            default:
                res = CURLSHE_BAD_OPTION; // Should not happen
                break;
        }

        // Optionally check the result of setting the option
        if (res != CURLSHE_OK) {
            // Handle error if needed
        }
    }

    // Call the function under test
    CURLSHcode result = curl_share_cleanup(share_handle);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}