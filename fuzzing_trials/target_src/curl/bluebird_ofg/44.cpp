#include "curl/curl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize CURLSH object
    CURLSH *share = curl_share_init();
    if (!share) {
        return 0;
    }

    // Ensure the data is large enough to extract an option and a valid option value
    if (size < sizeof(CURLSHoption) + 1) {
        curl_share_cleanup(share);
        return 0;
    }

    // Extract a CURLSHoption from the data
    CURLSHoption option = static_cast<CURLSHoption>(data[0] % CURLSHOPT_LAST);

    // Use the remaining data as the option value, ensure it's not null
    void *option_value = nullptr;
    if (option == CURLSHOPT_SHARE || option == CURLSHOPT_UNSHARE) {
        // These options expect a long value, ensure the data is large enough
        if (size >= sizeof(CURLSHoption) + sizeof(long)) {
            long share_value;
            memcpy(&share_value, data + 1, sizeof(long));
            option_value = (void *)&share_value;
        } else {
            curl_share_cleanup(share);
            return 0;
        }
    }

    // Call the function-under-test
    if (option_value != nullptr) {
        curl_share_setopt(share, option, option_value);
    }

    // Cleanup
    curl_share_cleanup(share);

    return 0;
}