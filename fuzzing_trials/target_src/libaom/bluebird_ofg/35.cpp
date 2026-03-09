#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_decode to aom_codec_get_frame

    aom_image_t* ret_aom_codec_get_frame_gdfuk = aom_codec_get_frame(&codec, NULL);
    if (ret_aom_codec_get_frame_gdfuk == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_get_frame to aom_img_get_metadata

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_get_frame to aom_img_plane_width

    int ret_aom_img_plane_width_iypyl = aom_img_plane_width(ret_aom_codec_get_frame_gdfuk, AOM_MAX_TILE_ROWS);
    if (ret_aom_img_plane_width_iypyl < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    size_t ret_aom_uleb_size_in_bytes_aylst = aom_uleb_size_in_bytes(64);
    if (ret_aom_uleb_size_in_bytes_aylst < 0){
    	return 0;
    }

    const aom_metadata_t* ret_aom_img_get_metadata_purhk = aom_img_get_metadata(ret_aom_codec_get_frame_gdfuk, ret_aom_uleb_size_in_bytes_aylst);
    if (ret_aom_img_get_metadata_purhk == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}