#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Include the necessary AOM codec headers
extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h> // Include this header for aom_codec_av1_dx
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Ensure the size is appropriate for creating a codec context
    if (size < sizeof(aom_codec_ctx_t)) {
        return 0; // Not enough data to create a codec context
    }

    // Initialize a codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_dec_cfg_t cfg = { 0 };
    aom_codec_err_t res;

    // Initialize the codec context
    // Corrected function call to include the codec interface and flags
    const aom_codec_iface_t *iface = aom_codec_av1_dx(); // Get the decoder interface for AV1
    res = aom_codec_dec_init(&codec_ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed
    }

    // Create a codec context with the provided data
    // Note: We are using the data to fill the codec context structure
    memcpy(&codec_ctx, data, sizeof(aom_codec_ctx_t));

    // Call the function under test
    const char *error_detail = aom_codec_error_detail(&codec_ctx);

    // Optionally, you can use the error_detail for further processing or logging
    // For fuzzing purposes, we just call the function to ensure it executes without crashing

    // Cleanup the codec context
    aom_codec_destroy(&codec_ctx);

    return 0;
}