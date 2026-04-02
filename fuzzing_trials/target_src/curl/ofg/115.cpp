#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize a CURLSH handle
    CURLSH *share_handle = curl_share_init();
    if (!share_handle) {
        return 0; // If initialization fails, return immediately
    }

    // Ensure the data size is sufficient for our needs
    if (size < 1) {
        curl_share_cleanup(share_handle);
        return 0;
    }

    // Extract a CURLSHoption from the data
    CURLSHoption option = static_cast<CURLSHoption>(data[0] % 3); // Limit to 3 valid options for demonstration

    // Prepare a non-NULL pointer for the value parameter
    void *value = nullptr;
    switch (option) {
        case CURLSHOPT_SHARE:
            value = reinterpret_cast<void *>(CURL_LOCK_DATA_COOKIE);
            break;
        case CURLSHOPT_UNSHARE:
            value = reinterpret_cast<void *>(CURL_LOCK_DATA_COOKIE);
            break;
        default:
            curl_share_cleanup(share_handle);
            return 0; // Return if option is not handled
    }

    // Call the function-under-test
    CURLSHcode result = curl_share_setopt(share_handle, option, value);

    // Clean up
    curl_share_cleanup(share_handle);

    return 0;
}