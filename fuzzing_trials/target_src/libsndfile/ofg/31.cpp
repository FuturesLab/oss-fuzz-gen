#include <stdint.h>
#include <stddef.h>
#include <sndfile.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    int sf_format_check(const SF_INFO *);
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to initialize SF_INFO
    if (size < sizeof(SF_INFO)) {
        return 0;
    }

    // Create an SF_INFO object and initialize it with data
    SF_INFO sfinfo;
    // Copy the data into sfinfo, ensuring that it doesn't exceed the size of SF_INFO
    memcpy(&sfinfo, data, sizeof(SF_INFO));

    // Call the function-under-test
    int result = sf_format_check(&sfinfo);

    // Return 0 as the function should not return any error code for the fuzzer
    return 0;
}