#include <cstdint>
#include <cstdlib>
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
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
    res = aom_codec_decode(&codec, data, size, nullptr);

    // Destroy the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_set_option

    aom_codec_err_t ret_aom_codec_set_option_qorln = aom_codec_set_option(&codec, (const char *)"w", (const char *)data);

    // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec);

    return 0;
}