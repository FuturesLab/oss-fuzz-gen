#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Call the function-under-test
    CURLSH *share_handle = curl_share_init();

    // Normally, you would perform operations on the share_handle here,
    // but since curl_share_init does not take any parameters nor does it
    // operate on input data directly, there's nothing to do with `data` and `size`.

    // Clean up the CURL share handle
    if (share_handle != NULL) {
        curl_share_cleanup(share_handle);
    }

    return 0;
}