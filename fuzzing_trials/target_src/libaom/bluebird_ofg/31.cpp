#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_av1_dx to aom_codec_iface_name

    const char* ret_aom_codec_iface_name_ulpzn = aom_codec_iface_name(iface);
    if (ret_aom_codec_iface_name_ulpzn == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    res = aom_codec_dec_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    res = aom_codec_decode(&codec, data, size, nullptr);

    // Destroy the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_decode
    aom_codec_caps_t ret_aom_codec_get_caps_vedff = aom_codec_get_caps(iface);
    if (ret_aom_codec_get_caps_vedff < 0){
    	return 0;
    }
    const char* ret_aom_codec_iface_name_nymqc = aom_codec_iface_name(iface);
    if (ret_aom_codec_iface_name_nymqc == NULL){
    	return 0;
    }

    aom_codec_err_t ret_aom_codec_decode_aavif = aom_codec_decode(&codec, (const uint8_t *)&ret_aom_codec_get_caps_vedff, 1, (void *)iface);

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}