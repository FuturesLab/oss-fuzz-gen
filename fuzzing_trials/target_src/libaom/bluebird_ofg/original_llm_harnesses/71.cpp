#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>

extern "C" {
    #include <aom/aomdx.h>
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for the test
    if (size < sizeof(aom_codec_ctx_t) + sizeof(aom_codec_stream_info_t)) {
        return 0;
    }

    // Initialize the codec context and stream info structures
    aom_codec_ctx_t codec_ctx;
    aom_codec_stream_info_t stream_info;

    // Initialize the codec context
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_err_t res = aom_codec_dec_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function under test
    res = aom_codec_get_stream_info(&codec_ctx, &stream_info);

    // Clean up the codec context
    aom_codec_destroy(&codec_ctx);

    return 0;
}