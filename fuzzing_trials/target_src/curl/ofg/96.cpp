#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Initialize a CURLSH object
    CURLSH *share = curl_share_init();
    if (!share) {
        return 0; // Return if initialization fails
    }

    // Define CURLSHoption and void* parameter
    CURLSHoption option;
    void *param = nullptr;

    // Ensure size is sufficient to extract option and param
    if (size >= sizeof(CURLSHoption) + sizeof(void *)) {
        // Extract CURLSHoption from data
        option = *(reinterpret_cast<const CURLSHoption *>(data));

        // Extract void* parameter from data
        param = *(reinterpret_cast<void *const *>(data + sizeof(CURLSHoption)));
    } else {
        // Use default values if size is insufficient
        option = CURLSHOPT_SHARE;
        param = reinterpret_cast<void *>(CURL_LOCK_DATA_COOKIE);
    }

    // Call the function-under-test
    curl_share_setopt(share, option, param);

    // Cleanup
    curl_share_cleanup(share);

    return 0;
}