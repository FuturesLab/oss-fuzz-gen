#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for strlen

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract an aom_codec_err_t value
    if (size < sizeof(aom_codec_err_t)) {
        return 0;
    }

    // Extract an aom_codec_err_t value from the input data
    aom_codec_err_t error_code = *(const aom_codec_err_t *)data;

    // Call the function-under-test
    const char *error_string = aom_codec_err_to_string(error_code);

    // Use the result in some way to prevent compiler optimizations
    if (error_string != NULL) {
        // Do something trivial with the error_string
        volatile size_t length = strlen(error_string);
        (void)length;
    }

    return 0;
}