#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "aom/aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom/aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {0};
    aom_codec_stream_info_t si;
    aom_codec_err_t res;

    // Initialize the decoder
    res = aom_codec_dec_init_ver(&ctx, iface, &cfg, 0, AOM_DECODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Set frame buffer functions with random function pointers

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_dec_init_ver to aom_codec_set_frame_buffer_functions
    const char* ret_aom_codec_iface_name_ddaws = aom_codec_iface_name(iface);
    if (ret_aom_codec_iface_name_ddaws == NULL){
    	return 0;
    }

    aom_codec_err_t ret_aom_codec_set_frame_buffer_functions_knbyv = aom_codec_set_frame_buffer_functions(&ctx, 0, 0, (void *)iface);

    // End mutation: Producer.APPEND_MUTATOR

    res = aom_codec_set_frame_buffer_functions(&ctx, nullptr, nullptr, nullptr);
    
    // Retrieve stream info
    res = aom_codec_get_stream_info(&ctx, &si);
    
    // Decode the input data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_get_stream_info to aom_codec_set_frame_buffer_functions

    aom_codec_err_t ret_aom_codec_set_frame_buffer_functions_ammkx = aom_codec_set_frame_buffer_functions(&ctx, 0, 0, (void *)iface);

    // End mutation: Producer.APPEND_MUTATOR

    res = aom_codec_decode(&ctx, Data, Size, nullptr);
    
    // Peek stream info without context
    res = aom_codec_peek_stream_info(iface, Data, Size, &si);

    // Cleanup
    aom_codec_destroy(&ctx);
    
    return 0;
}