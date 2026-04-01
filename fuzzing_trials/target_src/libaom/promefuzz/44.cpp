// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "aom/aom_integer.h"
#include "aom/aom_image.h"
#include "aom/aom_codec.h"
#include "aom/aom_frame_buffer.h"
#include "aom/aom_encoder.h"
#include "aom/aom_external_partition.h"
#include "aom/aom.h"
#include "aom/aom_decoder.h"
#include "aom/aomcx.h"
#include "aom/aomdx.h"

static aom_codec_ctx_t* initialize_codec() {
    aom_codec_ctx_t* codec = new aom_codec_ctx_t;
    memset(codec, 0, sizeof(aom_codec_ctx_t));
    codec->iface = aom_codec_av1_cx();
    codec->init_flags = 0;
    return codec;
}

static void cleanup_codec(aom_codec_ctx_t* codec) {
    if (codec) {
        aom_codec_destroy(codec);
        delete codec;
    }
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t* codec = initialize_codec();
    if (!codec) return 0;

    // Define control IDs
    int ctrl_id_obmc = AV1E_SET_ENABLE_OBMC;
    int ctrl_id_skip_postproc = AV1E_SET_SKIP_POSTPROC_FILTERING;
    int ctrl_id_tpl_model = AV1E_SET_ENABLE_TPL_MODEL;
    int ctrl_id_tile_rows = AV1E_SET_TILE_ROWS;
    int ctrl_id_tile_columns = AV1E_SET_TILE_COLUMNS;
    int ctrl_id_noise_sensitivity = AV1E_SET_NOISE_SENSITIVITY;

    // Fuzzing AV1E_SET_ENABLE_OBMC
    {
        unsigned int enable_obmc = Data[0] % 2;
        aom_codec_control(codec, ctrl_id_obmc, enable_obmc);
    }

    // Fuzzing AV1E_SET_SKIP_POSTPROC_FILTERING
    if (Size > 1) {
        unsigned int skip_filtering = Data[1] % 2;
        aom_codec_control(codec, ctrl_id_skip_postproc, skip_filtering);
    }

    // Fuzzing AV1E_SET_ENABLE_TPL_MODEL
    if (Size > 2) {
        unsigned int enable_tpl_model = Data[2] % 2;
        aom_codec_control(codec, ctrl_id_tpl_model, enable_tpl_model);
    }

    // Fuzzing AV1E_SET_TILE_ROWS
    if (Size > 3) {
        unsigned int tile_rows = Data[3] % 64; // Assuming a reasonable max tile row count
        aom_codec_control(codec, ctrl_id_tile_rows, tile_rows);
    }

    // Fuzzing AV1E_SET_TILE_COLUMNS
    if (Size > 4) {
        unsigned int tile_columns = Data[4] % 64; // Assuming a reasonable max tile column count
        aom_codec_control(codec, ctrl_id_tile_columns, tile_columns);
    }

    // Fuzzing AV1E_SET_NOISE_SENSITIVITY
    if (Size > 5) {
        unsigned int noise_sensitivity = Data[5] % 6; // Assuming noise sensitivity levels are from 0 to 5
        aom_codec_control(codec, ctrl_id_noise_sensitivity, noise_sensitivity);
    }

    cleanup_codec(codec);
    return 0;
}