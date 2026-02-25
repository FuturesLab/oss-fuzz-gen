#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>

extern "C" {
    aom_codec_err_t aom_codec_peek_stream_info(aom_codec_iface_t *, const uint8_t *, size_t, aom_codec_stream_info_t *);
    aom_codec_iface_t* aom_codec_av1_dx(); // Declare the AV1 decoder interface function
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    aom_codec_iface_t *codec_iface = aom_codec_av1_dx(); // Use AV1 decoder interface
    aom_codec_stream_info_t stream_info;

    // Initialize stream_info to ensure it is not NULL
    memset(&stream_info, 0, sizeof(stream_info));

    // Ensure size is within a reasonable limit for the codec
    if (size > 65536) {
        size = 65536; // Limit the size to prevent excessive memory usage
    }

    // Call the function under test
    aom_codec_err_t result = aom_codec_peek_stream_info(codec_iface, data, size, &stream_info);

    // Optionally check the result (not strictly necessary for fuzzing)
    if (result != AOM_CODEC_OK) {
        // Handle error if needed, but for fuzzing, we can ignore it
    }

    return 0;
}