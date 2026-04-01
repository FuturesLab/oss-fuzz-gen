#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx(); // Use a specific codec interface
    aom_codec_dec_cfg_t dec_cfg;
    aom_codec_flags_t flags = 0;
    int ver = AOM_DECODER_ABI_VERSION;

    // Ensure the data size is sufficient for initializing dec_cfg
    if (size < sizeof(aom_codec_dec_cfg_t)) {
        return 0;
    }

    // Copy data into dec_cfg
    std::memcpy(&dec_cfg, data, sizeof(aom_codec_dec_cfg_t));

    // Call the function under test
    aom_codec_err_t result = aom_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, flags, ver);

    // Clean up
    if (result == AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
    }

    return 0;
}