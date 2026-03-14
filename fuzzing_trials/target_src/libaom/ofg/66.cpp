#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include the necessary header for aom_codec_av1_dx
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_err_t res = aom_codec_dec_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Initialize stream info
    aom_codec_stream_info_t stream_info;
    stream_info.is_kf = 0; // Initialize to a default value

    // Call the function under test
    aom_codec_err_t err = aom_codec_get_stream_info(&codec_ctx, &stream_info);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}