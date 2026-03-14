#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of aom_codec_control
    aom_codec_err_t ret_aom_codec_control_yjtsg = aom_codec_control(&codec, AOM_MAX_TILE_ROWS);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_control
    aom_codec_caps_t ret_aom_codec_get_caps_boeri = aom_codec_get_caps(iface);
    if (ret_aom_codec_get_caps_boeri < 0){
    	return 0;
    }

    aom_codec_err_t ret_aom_codec_control_obvnb = aom_codec_control(&codec, (int )ret_aom_codec_get_caps_boeri);

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}