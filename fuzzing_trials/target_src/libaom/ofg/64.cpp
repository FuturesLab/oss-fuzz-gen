#include <stdint.h>
#include <stddef.h>
#include <aom/aom_codec.h>

extern "C" {
    // Include the necessary header for the function-under-test
    #include <aom/aom_codec.h>
}

// LLVMFuzzerTestOneInput function definition
extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract a valid aom_codec_err_t value
    if (size < sizeof(aom_codec_err_t)) {
        return 0;
    }

    // Cast the input data to an aom_codec_err_t type
    aom_codec_err_t codec_error = *(reinterpret_cast<const aom_codec_err_t*>(data));

    // Call the function-under-test
    const char *error_string = aom_codec_err_to_string(codec_error);

    // Use the error_string in some way to prevent compiler optimizations from removing the call
    if (error_string != NULL) {
        // Do something trivial with error_string, like checking its length
        volatile size_t length = 0;
        while (error_string[length] != '\0') {
            length++;
        }
    }

    return 0;
}