#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size < sizeof(long)) {
        return 0;
    }

    // Extract a long value from the input data
    long init_option = 0;
    for (size_t i = 0; i < sizeof(long) && i < size; ++i) {
        init_option |= ((long)data[i]) << (i * 8);
    }

    // Call the function-under-test
    CURLcode result = curl_global_init(init_option);

    // Optionally handle the result or perform additional operations

    return 0;
}