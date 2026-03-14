#include "stdint.h"
#include "stddef.h"

extern "C" {
    #include "/src/aom/aom/aom_codec.h"
    #include "aom/aom_decoder.h"
    #include "aom/aomdx.h"  // Include the header where aom_codec_av1_dx is declared
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Initialize the codec interface
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Ensure the data size is non-zero for meaningful testing
    if (size == 0) {
        return 0;
    }

    // Initialize stream info structure
    aom_codec_stream_info_t stream_info;
    stream_info.is_kf = 0;  // Initialize with a default value

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_peek_stream_info(iface, data, size, &stream_info);

    // Optionally, handle the result or check for specific conditions
    // For fuzzing purposes, we are primarily interested in finding crashes or unexpected behavior

    return 0;
}