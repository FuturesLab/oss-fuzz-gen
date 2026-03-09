#include <cstddef>
#include <cstdint>
#include <cstring> // Include for memset

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h> // Include the header for the VP8 decoder
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    if (size < 10) { // Ensure there's enough data to be meaningful
        return 0;
    }

    // Declare and initialize variables
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Example interface for VP8
    const uint8_t *buffer = data;
    unsigned int buffer_size = static_cast<unsigned int>(size);

    // Initialize stream_info with zeros
    vpx_codec_stream_info_t stream_info;
    memset(&stream_info, 0, sizeof(vpx_codec_stream_info_t));
    stream_info.sz = sizeof(vpx_codec_stream_info_t); // Initialize the size field

    // Call the function-under-test
    vpx_codec_err_t result = vpx_codec_peek_stream_info(iface, buffer, buffer_size, &stream_info);

    // Check the result and use stream_info to maximize code coverage
    if (result == VPX_CODEC_OK && stream_info.is_kf) { // Check if it's a keyframe
        vpx_codec_ctx_t codec;
        if (vpx_codec_dec_init(&codec, iface, nullptr, 0) == VPX_CODEC_OK) {
            if (vpx_codec_decode(&codec, buffer, buffer_size, nullptr, 0) == VPX_CODEC_OK) {
                vpx_codec_iter_t iter = nullptr;
                vpx_image_t *img = nullptr;
                while ((img = vpx_codec_get_frame(&codec, &iter)) != nullptr) {
                    // Process the image to increase code coverage
                    // For example, access some image properties
                    volatile int width = img->d_w;
                    volatile int height = img->d_h;
                    volatile int stride = img->stride[0];
                    (void)width;
                    (void)height;
                    (void)stride;
                }
            }
            vpx_codec_destroy(&codec);
        }
    }

    // Return 0 to indicate the fuzzer should continue
    return 0;
}