#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>

extern "C" {
    // Include the necessary header for the function-under-test
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an aom_codec_err_t value
    if (size < sizeof(aom_codec_err_t)) {
        return 0;
    }

    // Extract an aom_codec_err_t value from the input data
    aom_codec_err_t error_code = *(reinterpret_cast<const aom_codec_err_t*>(data));

    // Call the function-under-test
    const char *error_string = aom_codec_err_to_string(error_code);

    // Use the error_string in some way to prevent compiler optimizations from removing the call
    if (error_string != nullptr) {
        // For example, we could print it or perform some operation
        // Here, we simply ensure it's not null
        volatile const char *volatile_string = error_string;
        (void)volatile_string;
    }

    return 0;
}