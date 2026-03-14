#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
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
    size_t ret_aom_uleb_size_in_bytes_nbxjf = aom_uleb_size_in_bytes(AOM_PLANE_U);
    if (ret_aom_uleb_size_in_bytes_nbxjf < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_uleb_size_in_bytes to aom_codec_decode
    aom_codec_err_t ret_aom_codec_destroy_gtqtq = aom_codec_destroy(&codec);
    const uint8_t jdlyiuan = 1;

    aom_codec_err_t ret_aom_codec_decode_qjupc = aom_codec_decode(&codec, &jdlyiuan, ret_aom_uleb_size_in_bytes_nbxjf, (void *)"w");

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_err_t ret_aom_codec_control_mwmak = aom_codec_control(&codec, (int )ret_aom_uleb_size_in_bytes_nbxjf);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_decode
    const uint8_t gcxhvpug = size;

    aom_codec_err_t ret_aom_codec_decode_mxgfl = aom_codec_decode(&codec, &gcxhvpug, -1, (void *)&codec);

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}