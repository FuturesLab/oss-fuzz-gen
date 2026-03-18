// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1796:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_set_frame_buffer_functions at aom_decoder.c:120:17 in aom_decoder.h
// aom_codec_get_stream_info at aom_decoder.c:75:17 in aom_decoder.h
// aom_codec_decode at aom_decoder.c:94:17 in aom_decoder.h
// aom_codec_peek_stream_info at aom_decoder.c:57:17 in aom_decoder.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {0};
    aom_codec_stream_info_t si;
    aom_codec_err_t res;

    // Initialize the decoder
    res = aom_codec_dec_init_ver(&ctx, iface, &cfg, 0, AOM_DECODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) return 0;

    // Set frame buffer functions with random function pointers
    res = aom_codec_set_frame_buffer_functions(&ctx, nullptr, nullptr, nullptr);
    
    // Retrieve stream info
    res = aom_codec_get_stream_info(&ctx, &si);
    
    // Decode the input data
    res = aom_codec_decode(&ctx, Data, Size, nullptr);
    
    // Peek stream info without context
    res = aom_codec_peek_stream_info(iface, Data, Size, &si);

    // Cleanup
    aom_codec_destroy(&ctx);
    
    return 0;
}