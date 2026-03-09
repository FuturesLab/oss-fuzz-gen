#include <cstddef>
#include <cstdint>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include the header file where aom_codec_av1_dx is declared
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Initialize the codec interface
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the stream info structure
    aom_codec_stream_info_t stream_info;
    stream_info.is_annexb = 0; // Initialize the is_annexb field

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_peek_stream_info(iface, data, size, &stream_info);

    // Use the result to prevent any compiler optimizations that might skip the function call
    if (result == AOM_CODEC_OK) {
        // Optionally, perform some operations with stream_info
        // For example, check the width and height
        volatile unsigned int width = stream_info.w;
        volatile unsigned int height = stream_info.h;
    }

    return 0;
}