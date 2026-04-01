#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vpx_codec.h>
#include <vpx/vp8dx.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Declare and initialize the necessary variables
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Use VP8 decoder interface
    vpx_codec_ctx_t codec;
    vpx_codec_err_t result;

    // Ensure the data size is within a reasonable range
    if (size > 10) { // Ensure there's enough data for a valid VP8 header
        // Initialize the decoder
        result = vpx_codec_dec_init(&codec, iface, NULL, 0);
        if (result == VPX_CODEC_OK) {
            // Decode the input data
            result = vpx_codec_decode(&codec, data, (unsigned int)size, NULL, 0);
            if (result == VPX_CODEC_OK) {
                // Retrieve frame to ensure decoding is processed
                vpx_codec_iter_t iter = NULL;
                vpx_image_t *img = NULL;
                while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
                    // Process the image (if necessary)
                    // For fuzzing, we don't need to process the image further
                }
            } else {
                // Handle decoding error for fuzzing feedback
                const char* error_msg = vpx_codec_err_to_string(result);
                if (error_msg) {
                    // Log the error message for better fuzzing feedback
                    std::cerr << "Decoding error: " << error_msg << std::endl;
                }
            }
            // Destroy the codec context
            vpx_codec_destroy(&codec);
        } else {
            // Handle initialization error for fuzzing feedback
            const char* error_msg = vpx_codec_err_to_string(result);
            if (error_msg) {
                // Log the error message for better fuzzing feedback
                std::cerr << "Initialization error: " << error_msg << std::endl;
            }
        }
    } else {
        std::cerr << "Input data size too small for valid VP8 header." << std::endl;
    }

    return 0;
}