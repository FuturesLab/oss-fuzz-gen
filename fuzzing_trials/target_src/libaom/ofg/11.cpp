#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>

extern "C" {
    #include <aom/aomcx.h> // Include the correct header for aom_codec_av1_cx
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize variables
    aom_codec_ctx_t codec;
    int control_id;
    void *control_data;

    // Ensure the size is sufficient to extract control_id and control_data
    if (size < sizeof(int) + sizeof(void *)) {
        return 0;
    }

    // Extract control_id and control_data from the input data
    control_id = *(reinterpret_cast<const int *>(data));
    control_data = const_cast<void *>(reinterpret_cast<const void *>(data + sizeof(int)));

    // Initialize the codec context
    if (aom_codec_enc_init(&codec, aom_codec_av1_cx(), nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    aom_codec_err_t result = aom_codec_control(&codec, control_id, control_data);

    // Destroy the codec context
    aom_codec_destroy(&codec);

    return 0;
}