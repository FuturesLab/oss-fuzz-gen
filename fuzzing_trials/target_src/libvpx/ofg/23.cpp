#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8dx.h> // Include the header where vpx_codec_vp8_dx is declared
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Check if the input size is too small to be a valid stream
    if (size < 10) { // Assuming a minimal size for a valid VP8 stream
        return 0;
    }

    // Declare and initialize variables
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Example interface, assuming VP8
    vpx_codec_ctx_t codec;
    vpx_codec_err_t result;
    vpx_codec_stream_info_t stream_info;

    // Initialize stream_info
    stream_info.sz = sizeof(vpx_codec_stream_info_t);

    // Ensure that the interface is not NULL
    if (iface == NULL) {
        return 0;
    }

    // Initialize the codec context
    result = vpx_codec_dec_init(&codec, iface, NULL, 0);
    if (result != VPX_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    result = vpx_codec_peek_stream_info(iface, data, static_cast<unsigned int>(size), &stream_info);
    if (result != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Decode the input data
    result = vpx_codec_decode(&codec, data, static_cast<unsigned int>(size), NULL, 0);
    if (result != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Retrieve the decoded frame
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img = NULL;
    while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
        // Process the image as needed
        // For fuzzing purposes, we can access some properties to ensure the image is being processed
        volatile int width = img->d_w;
        volatile int height = img->d_h;
        (void)width;
        (void)height;
    }

    // Destroy the codec context
    vpx_codec_destroy(&codec);

    return 0;
}