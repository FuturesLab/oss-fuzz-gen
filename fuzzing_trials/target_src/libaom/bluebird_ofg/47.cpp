#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the codec context
    res = aom_codec_dec_init(&codec, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of aom_codec_decode
    res = aom_codec_decode(&codec, data, size, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Destroy the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_decode

    aom_codec_err_t ret_aom_codec_decode_jzjlr = aom_codec_decode(&codec, NULL, AOM_PLANE_PACKED, (void *)data);

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}