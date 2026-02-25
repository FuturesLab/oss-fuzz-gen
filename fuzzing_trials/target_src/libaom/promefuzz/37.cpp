// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_dx at av1_dx_iface.c:1796:20 in aomdx.h
// aom_codec_dec_init_ver at aom_decoder.c:25:17 in aom_decoder.h
// aom_codec_iface_name at aom_codec.c:32:13 in aom_codec.h
// aom_codec_get_caps at aom_codec.c:84:18 in aom_codec.h
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
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg_t cfg = {};
    aom_codec_stream_info_t si = {};
    aom_codec_err_t res;

    // Initialize decoder context
    res = aom_codec_dec_init_ver(&ctx, iface, &cfg, 0, AOM_DECODER_ABI_VERSION);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed
    }

    // Fuzzing aom_codec_iface_name
    const char *iface_name = aom_codec_iface_name(iface);

    // Fuzzing aom_codec_get_caps
    aom_codec_caps_t caps = aom_codec_get_caps(iface);

    // Fuzzing aom_codec_peek_stream_info
    res = aom_codec_peek_stream_info(iface, Data, Size, &si);
    if (res == AOM_CODEC_OK) {
        // Successfully parsed stream info
    }

    // Cleanup
    aom_codec_destroy(&ctx);
    return 0;
}