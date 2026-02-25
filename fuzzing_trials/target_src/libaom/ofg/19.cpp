#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_codec.h>

extern "C" {

const char *aom_codec_error(const aom_codec_ctx_t *);

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure that size is large enough for aom_codec_ctx_t
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0;
    }

    // Declare and initialize the codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx)); // Initialize the codec context to zero

    // Copy the input data into the codec context
    memcpy(&codec_ctx, data, sizeof(aom_codec_ctx_t));

    // Call the function under test
    const char *error_message = aom_codec_error(&codec_ctx);

    // Optionally, you can do something with the error message here
    // For example, you could print it or log it, but this is not necessary for fuzzing

    return 0;
}

}