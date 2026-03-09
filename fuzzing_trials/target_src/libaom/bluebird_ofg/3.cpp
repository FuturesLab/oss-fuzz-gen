#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the codec context
    res = aom_codec_dec_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    res = aom_codec_decode(&codec, data, size, nullptr);

    // Destroy the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_decode to aom_codec_set_frame_buffer_functions

    aom_codec_err_t ret_aom_codec_set_frame_buffer_functions_cxmbv = aom_codec_set_frame_buffer_functions(&codec, 0, 0, (void *)iface);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_set_frame_buffer_functions to aom_codec_control

    aom_codec_err_t ret_aom_codec_control_yjtsg = aom_codec_control(&codec, size);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_dec_init_ver

    aom_codec_err_t ret_aom_codec_dec_init_ver_mzhyl = aom_codec_dec_init_ver(&codec, NULL, NULL, AOM_PLANE_PACKED, AOM_IMAGE_ABI_VERSION);

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}