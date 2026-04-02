#include <stdint.h>
#include <stddef.h>
#include "curl/curl.h"

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    CURLSH *share;
    CURLSHcode result;

    // Initialize a CURL share handle
    share = curl_share_init();
    if (!share) {
        return 0;
    }

    // Ensure the data size is sufficient for our needs
    if (size < 1) {
        curl_share_cleanup(share);
        return 0;
    }

    // Use the first byte of data to determine the CURLSHoption
    CURLSHoption option = static_cast<CURLSHoption>(data[0] % CURLSHOPT_LAST);

    // Call the function-under-test with different options
    switch (option) {
        case CURLSHOPT_SHARE:
        case CURLSHOPT_UNSHARE:
            // For these options, a CURL_LOCK_DATA value is needed
            if (size > 1) {
                curl_lock_data data_option = static_cast<curl_lock_data>(data[1] % CURL_LOCK_DATA_LAST);
                result = curl_share_setopt(share, option, (void *)(intptr_t)data_option);
            }
            break;
        case CURLSHOPT_LOCKFUNC:
        case CURLSHOPT_UNLOCKFUNC:
            // For these options, a function pointer is needed
            result = curl_share_setopt(share, option, NULL);
            break;
        case CURLSHOPT_USERDATA:
            // For this option, a user data pointer is needed
            result = curl_share_setopt(share, option, (void *)(intptr_t)data);
            break;
        default:
            // Handle any other options that might be added in the future
            result = curl_share_setopt(share, option, NULL);
            break;
    }

    // Cleanup the CURL share handle
    curl_share_cleanup(share);

    return 0;
}