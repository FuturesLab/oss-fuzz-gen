// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aomcx.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aom_decoder.h"
#include "aomdx.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_integer.h"

// Helper function to perform codec control operations
static void fuzz_codec_control(aom_codec_ctx_t *codec_ctx, const uint8_t *Data, size_t Size) {
    if (Size < 5) return;

    // Randomly decide which control function to call
    int control_id = Data[0] % 6;
    unsigned int param = Data[1]; // Use a simple parameter for control functions

    switch (control_id) {
        case 0:
            aom_codec_control(codec_ctx, AV1E_SET_SKIP_POSTPROC_FILTERING, param);
            break;
        case 1:
            aom_codec_control(codec_ctx, AV1E_SET_TILE_COLUMNS, param);
            break;
        case 2:
            aom_codec_control(codec_ctx, AV1E_SET_FORCE_VIDEO_MODE, param);
            break;
        case 3:
            aom_codec_control(codec_ctx, AV1E_SET_SUPERBLOCK_SIZE, param);
            break;
        case 4:
            aom_codec_control(codec_ctx, AV1E_SET_ENABLE_OBMC, param);
            break;
        case 5:
            aom_codec_control(codec_ctx, AV1E_SET_ENABLE_QM, param);
            break;
        default:
            break;
    }
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec context
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (aom_codec_enc_init(&codec_ctx, iface, nullptr, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Invoke the codec control functions with fuzz data
    fuzz_codec_control(&codec_ctx, Data, Size);

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}