#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8dx.h> // Include the header for vpx_codec_vp8_dx
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Check if the input data is large enough to be meaningful
    if (size < 10) { // Adjusted to ensure there's enough data for a valid frame
        return 0;
    }

    // Declare and initialize the necessary structures
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_stream_info_t stream_info;

    // Initialize the stream_info structure with default values
    memset(&stream_info, 0, sizeof(vpx_codec_stream_info_t));
    stream_info.sz = sizeof(vpx_codec_stream_info_t);

    // Peek into the stream to check if it's a valid VPX stream
    if (vpx_codec_peek_stream_info(vpx_codec_vp8_dx(), data, size, &stream_info) != VPX_CODEC_OK) {
        return 0; // If not a valid stream, exit early
    }

    // Initialize the codec context
    vpx_codec_err_t init_result = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), NULL, 0);
    if (init_result != VPX_CODEC_OK) {
        return 0;
    }

    // Decode the input data
    vpx_codec_err_t decode_result = vpx_codec_decode(&codec_ctx, data, size, NULL, 0);
    if (decode_result == VPX_CODEC_OK) {
        // Try to retrieve a frame to ensure the input is being processed
        vpx_codec_iter_t iter = NULL;
        vpx_image_t *img = NULL;

        while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
            // Process the image/frame if needed
            // For fuzzing purposes, we just retrieve the frame to ensure processing
        }
    }

    // Retrieve the stream information after decoding
    vpx_codec_err_t result = vpx_codec_get_stream_info(&codec_ctx, &stream_info);

    // Cleanup
    vpx_codec_destroy(&codec_ctx);

    return 0;
}