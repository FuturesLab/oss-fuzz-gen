#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include the header for AV1 decoder interface
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize the codec interface
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Ensure the data is not NULL and size is greater than zero
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Initialize stream info
    aom_codec_stream_info_t stream_info;
    stream_info.is_annexb = 0; // Set a default value

    // Call the function under test
    aom_codec_err_t result = aom_codec_peek_stream_info(iface, data, size, &stream_info);

    // Check the result (this is optional, but useful for debugging)
    if (result != AOM_CODEC_OK) {
        // Handle error if needed
    }

    return 0;
}