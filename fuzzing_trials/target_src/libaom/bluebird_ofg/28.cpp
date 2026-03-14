#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_av1_dx to aom_codec_set_frame_buffer_functions


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_av1_dx to aom_codec_peek_stream_info
    size_t ret_aom_uleb_size_in_bytes_srcpz = aom_uleb_size_in_bytes(AOM_MAX_TILE_ROWS);
    if (ret_aom_uleb_size_in_bytes_srcpz < 0){
    	return 0;
    }
    const uint8_t paiwhecn = size;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of aom_codec_peek_stream_info
    const uint8_t kjjriigc = -1;
    aom_codec_err_t ret_aom_codec_peek_stream_info_hxkvy = aom_codec_peek_stream_info(iface, &kjjriigc, ret_aom_uleb_size_in_bytes_srcpz, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_err_t ret_aom_codec_set_frame_buffer_functions_rcqha = aom_codec_set_frame_buffer_functions(NULL, 0, 0, (void *)iface);

    // End mutation: Producer.APPEND_MUTATOR

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

    aom_codec_destroy(&codec);

    return 0;
}