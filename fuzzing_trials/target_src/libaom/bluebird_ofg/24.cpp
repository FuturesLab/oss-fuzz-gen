#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_control
    aom_codec_caps_t ret_aom_codec_get_caps_pcads = aom_codec_get_caps(iface);
    if (ret_aom_codec_get_caps_pcads < 0){
    	return 0;
    }

    aom_codec_err_t ret_aom_codec_control_nrsms = aom_codec_control(&codec, (int )ret_aom_codec_get_caps_pcads);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_dec_init_ver


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of aom_codec_dec_init_ver
    aom_codec_err_t ret_aom_codec_dec_init_ver_ekolf = aom_codec_dec_init_ver(&codec, NULL, NULL, AOM_MAX_TILE_COLS, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}