#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of a long
    if (size < sizeof(long)) {
        return 0;
    }

    // Interpret the first bytes of data as a long
    long init_flags = 0;
    for (size_t i = 0; i < sizeof(long); ++i) {
        init_flags |= ((long)data[i] << (i * 8));
    }

    // Call the function-under-test
    CURLcode result = curl_global_init(init_flags);

    // Optionally, handle the result or perform additional operations

    return 0;
}