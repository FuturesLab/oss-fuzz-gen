#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a long value
    if (size < sizeof(long)) {
        return 0;
    }

    // Extract a long value from the input data
    long init_flags = 0;
    for (size_t i = 0; i < sizeof(long); ++i) {
        init_flags |= ((long)data[i]) << (i * 8);
    }

    // Call the function-under-test
    CURLcode result = curl_global_init(init_flags);

    // You can optionally handle the result if needed
    // For fuzzing purposes, we typically just call the function

    return 0;
}