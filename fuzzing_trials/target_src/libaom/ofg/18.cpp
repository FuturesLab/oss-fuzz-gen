#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Include the necessary AOM codec headers
extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h> // Include the decoder header for aom_codec_av1_dx
#include <aom/aomdx.h> // Include the header for aom_codec_av1_dx
}

// Fuzzing harness for the aom_codec_error function
extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t res;

    // Initialize the codec context
    res = aom_codec_dec_init(&codec_ctx, aom_codec_av1_dx(), NULL, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed, exit early
    }

    // Create a buffer for input data
    uint8_t *input_data = (uint8_t *)malloc(size);
    if (input_data == NULL) {
        aom_codec_destroy(&codec_ctx);
        return 0; // Memory allocation failed, exit early
    }

    // Copy the input data into the buffer
    memcpy(input_data, data, size);

    // Use the input data in aom_codec_error
    const char *error_message = aom_codec_error(&codec_ctx);

    // Optionally, you can print or log the error message
    // printf("Error message: %s\n", error_message);

    // Clean up
    free(input_data);
    aom_codec_destroy(&codec_ctx);

    return 0;
}