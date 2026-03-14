#include <stdint.h>
#include <stddef.h>
#include <aom/aom_codec.h>

extern "C" {
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include the header for aom_codec_av1_dx
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract meaningful values
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t codec_err;

    // Initialize the codec context with the AV1 decoder interface
    codec_err = aom_codec_dec_init(&codec_ctx, aom_codec_av1_dx(), NULL, 0);
    if (codec_err != AOM_CODEC_OK) {
        return 0;
    }

    // Extract an integer command from the data
    int command = *(const int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Use the remaining data as the void* parameter
    void *control_data = (void *)data;

    // Call the function-under-test
    codec_err = aom_codec_control(&codec_ctx, command, control_data);

    // Destroy the codec context
    aom_codec_destroy(&codec_ctx);

    return 0;
}