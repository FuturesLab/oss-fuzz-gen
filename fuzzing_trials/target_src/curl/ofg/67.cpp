#include <curl/curl.h>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle) {
        return 0;
    }

    // Ensure the data is large enough to extract meaningful inputs
    if (size < sizeof(CURLMoption) + sizeof(void *)) {
        curl_multi_cleanup(multi_handle);
        return 0;
    }

    // Extract a CURLMoption from the data
    CURLMoption option;
    std::memcpy(&option, data, sizeof(CURLMoption));

    // Extract a void pointer from the data
    void *ptr;
    std::memcpy(&ptr, data + sizeof(CURLMoption), sizeof(void *));

    // Call the function-under-test
    curl_multi_setopt(multi_handle, option, ptr);

    // Clean up
    curl_multi_cleanup(multi_handle);

    return 0;
}