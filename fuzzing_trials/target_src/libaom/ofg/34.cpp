#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include the header for AV1 decoder interface
}

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Initialize the codec interface
    aom_codec_iface_t *iface = aom_codec_av1_dx(); // Ensure the correct function is used

    // Ensure the interface is not NULL
    if (iface == NULL) {
        return 0;
    }

    // Initialize the stream info structure
    aom_codec_stream_info_t stream_info;
    stream_info.w = 0; // Initialize width to a known value
    stream_info.h = 0; // Initialize height to a known value
    stream_info.is_kf = 0; // Initialize to a known value

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_peek_stream_info(iface, data, size, &stream_info);

    // Check the result (optional, mainly for debugging purposes)
    if (result != AOM_CODEC_OK) {
        // Handle error if necessary
    }

    return 0;
}