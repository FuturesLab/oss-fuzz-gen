#include <stdint.h>
#include <stddef.h>
#include <limits.h> // Include for UINT_MAX

extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8dx.h> // Include for vpx_codec_vp8_dx
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize codec interface and stream info structures
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Using VP8 decoder as an example
    vpx_codec_stream_info_t stream_info;
    vpx_codec_err_t result;

    // Ensure the data size is within a reasonable range for the function
    if (size > 0 && size <= UINT_MAX) {
        // Call the function-under-test
        result = vpx_codec_peek_stream_info(iface, data, (unsigned int)size, &stream_info);
    }

    return 0;
}