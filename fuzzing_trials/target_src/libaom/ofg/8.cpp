#include <cstdint>
#include <cstdlib>
#include <aom/aom_decoder.h>
#include <aom/aom_codec.h>

extern "C" {
    #include <aom/aomdx.h>  // Include the header where aom_codec_av1_dx is declared
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize variables
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();  // Use AV1 decoder interface
    aom_codec_dec_cfg_t dec_cfg;
    aom_codec_flags_t flags = 0;
    int ver = AOM_DECODER_ABI_VERSION;

    // Ensure the data is non-null and has a minimum size for configuration
    if (size < sizeof(aom_codec_dec_cfg_t)) {
        return 0;
    }

    // Populate dec_cfg with some values derived from input data
    dec_cfg.threads = data[0] % 4 + 1;  // Number of threads between 1 and 4
    dec_cfg.w = (data[1] << 8) | data[2];  // Width from data
    dec_cfg.h = (data[3] << 8) | data[4];  // Height from data

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, flags, ver);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}