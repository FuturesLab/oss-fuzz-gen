#include <cstdint>
#include <curl/curl.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Initialize CURLM handle
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Ensure the data size is sufficient for our needs
    if (size < sizeof(CURLMoption) + sizeof(long)) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Extract CURLMoption from the data
    CURLMoption option = static_cast<CURLMoption>(data[0]);

    // Prepare a buffer to hold the option value
    char option_value[256];
    memset(option_value, 0, sizeof(option_value));

    // Copy data into option_value, ensuring we don't exceed the buffer size
    size_t copy_size = size - 1 < sizeof(option_value) ? size - 1 : sizeof(option_value) - 1;
    memcpy(option_value, data + 1, copy_size);

    // Call the function-under-test
    curl_multi_setopt(multi_handle, option, static_cast<void *>(option_value));

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}