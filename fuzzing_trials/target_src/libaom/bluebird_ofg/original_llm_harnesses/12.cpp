#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to extract meaningful data
    if (size < sizeof(aom_codec_ctx_t) + sizeof(int)) {
        return 0;
    }

    // Initialize aom_codec_ctx_t
    aom_codec_ctx_t codec_ctx;
    codec_ctx.name = "test_codec";
    codec_ctx.priv = nullptr;
    codec_ctx.iface = nullptr;
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.err_detail = nullptr;
    codec_ctx.init_flags = 0;

    // Extract an integer command from the input data
    int command = *reinterpret_cast<const int*>(data);

    // Use the remaining data as the control data
    void* control_data = const_cast<uint8_t*>(data + sizeof(int));

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_control(&codec_ctx, command, control_data);

    // Return 0 to indicate successful execution
    return 0;
}