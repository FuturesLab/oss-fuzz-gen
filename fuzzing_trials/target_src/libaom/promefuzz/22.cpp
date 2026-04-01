// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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
#include <iostream>
#include <fstream>
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aom_decoder.h"
#include "aomcx.h"
#include "aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    int param_value = *reinterpret_cast<const int*>(Data);

    // Define control IDs
    const int AV1E_SET_FRAME_PERIODIC_BOOST = 1;
    const int AV1E_SET_SKIP_POSTPROC_FILTERING = 2;
    const int AV1E_SET_TILE_ROWS = 3;
    const int AV1E_SET_DISABLE_TRELLIS_QUANT = 4;
    const int AV1E_SET_ENABLE_RESTORATION = 5;
    const int AV1E_SET_ENABLE_OBMC = 6;

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FRAME_PERIODIC_BOOST
    aom_codec_control(&codec_ctx, AV1E_SET_FRAME_PERIODIC_BOOST, param_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING
    aom_codec_control(&codec_ctx, AV1E_SET_SKIP_POSTPROC_FILTERING, param_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TILE_ROWS
    aom_codec_control(&codec_ctx, AV1E_SET_TILE_ROWS, param_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_DISABLE_TRELLIS_QUANT
    aom_codec_control(&codec_ctx, AV1E_SET_DISABLE_TRELLIS_QUANT, param_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_RESTORATION
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_RESTORATION, param_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC
    aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_OBMC, param_value);

    return 0;
}