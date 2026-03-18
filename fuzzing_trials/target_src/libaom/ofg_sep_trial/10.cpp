#include <cstdint>
#include <cstdlib>

// Wrap the libaom includes with extern "C" since they are C libraries
extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_encoder.h>
    #include <aom/aomcx.h>
}

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize the codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg cfg;  // Use correct type name without _t
    aom_codec_err_t res;

    // Initialize codec configuration
    res = aom_codec_enc_config_default(iface, &cfg, AOM_USAGE_GOOD_QUALITY);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Initialize the codec
    res = aom_codec_enc_init(&codec_ctx, iface, &cfg, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Ensure the data size is sufficient for the control ID and arbitrary data
    if (size < sizeof(int) + 1) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Extract control ID and arbitrary data from fuzz input
    int control_id = *(reinterpret_cast<const int*>(data));
    const void *control_data = static_cast<const void*>(data + sizeof(int));

    // Call the function-under-test
    res = aom_codec_control(&codec_ctx, control_id, const_cast<void*>(control_data));

    // Clean up
    aom_codec_destroy(&codec_ctx);

    return 0;
}