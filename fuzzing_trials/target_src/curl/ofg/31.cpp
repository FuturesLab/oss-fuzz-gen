#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of a long
    if (size < sizeof(long)) {
        return 0;
    }

    // Extract a long value from the data
    long init_option = 0;
    for (size_t i = 0; i < sizeof(long) && i < size; ++i) {
        init_option |= ((long)data[i]) << (i * 8);
    }

    // Call the function-under-test with the extracted long value
    CURLcode result = curl_global_init(init_option);

    // Optionally, handle the result if needed
    // For fuzzing purposes, we just return 0 to continue testing
    return 0;
}