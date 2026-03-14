#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_av1_dx to aom_codec_set_frame_buffer_functions


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of aom_codec_set_frame_buffer_functions
    aom_codec_err_t ret_aom_codec_set_frame_buffer_functions_bapcz = aom_codec_set_frame_buffer_functions(NULL, 0, 0, (void *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    res = aom_codec_dec_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of aom_codec_decode
    res = aom_codec_decode(&codec, data, size, (void *)data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Destroy the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_decode to aom_codec_control
    aom_codec_caps_t ret_aom_codec_get_caps_btjxy = aom_codec_get_caps(NULL);
    if (ret_aom_codec_get_caps_btjxy < 0){
    	return 0;
    }

    aom_codec_err_t ret_aom_codec_control_gsphm = aom_codec_control(&codec, (int )ret_aom_codec_get_caps_btjxy);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_control to aom_codec_decode
    size_t ret_aom_img_num_metadata_lehva = aom_img_num_metadata(NULL);
    if (ret_aom_img_num_metadata_lehva < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_img_num_metadata to aom_uleb_encode_fixed_size
    size_t ret_aom_uleb_size_in_bytes_fopxx = aom_uleb_size_in_bytes((uint64_t )ret_aom_codec_get_caps_btjxy);
    if (ret_aom_uleb_size_in_bytes_fopxx < 0){
    	return 0;
    }
    uint8_t buhchzpz = 0;

    int ret_aom_uleb_encode_fixed_size_ucolv = aom_uleb_encode_fixed_size((uint64_t )ret_aom_uleb_size_in_bytes_fopxx, AOM_IMAGE_ABI_VERSION, 1, &buhchzpz, &ret_aom_img_num_metadata_lehva);
    if (ret_aom_uleb_encode_fixed_size_ucolv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    size_t ret_aom_uleb_size_in_bytes_ycogb = aom_uleb_size_in_bytes(AOM_MAX_TILE_COLS);
    if (ret_aom_uleb_size_in_bytes_ycogb < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of aom_codec_decode

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of aom_codec_decode
    const uint8_t fchzjupy = 0;
    aom_codec_err_t ret_aom_codec_decode_lpatv = aom_codec_decode(NULL, &fchzjupy, ret_aom_uleb_size_in_bytes_ycogb, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}