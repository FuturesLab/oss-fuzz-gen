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
#include <cstdint>
#include <cstdlib>
#include <cstdio>
extern "C" {
#include <aom/aom_codec.h>
#include <aom/aom_encoder.h>
#include <aom/aomcx.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <aom/aom.h>
#include <aom/aom_image.h>
#include <aom/aom_integer.h>
#include <aom/aom_frame_buffer.h>
#include <aom/aom_external_partition.h>
}

static void InitializeCodecContext(aom_codec_ctx_t &codec_ctx) {
    codec_ctx.name = "AV1 Codec";
    codec_ctx.iface = aom_codec_av1_cx();
    codec_ctx.err = AOM_CODEC_OK;
    codec_ctx.init_flags = 0;
    codec_ctx.priv = nullptr;
}

static void CleanupCodecContext(aom_codec_ctx_t &codec_ctx) {
    aom_codec_destroy(&codec_ctx);
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    InitializeCodecContext(codec_ctx);

    int control_id = Data[0] % 6;
    int value = *reinterpret_cast<const int*>(Data);

    aom_codec_err_t res = AOM_CODEC_OK;
    switch (control_id) {
        case 0:
            res = aom_codec_control(&codec_ctx, AV1E_SET_COLOR_PRIMARIES, value);
            break;
        case 1:
            res = aom_codec_control(&codec_ctx, AV1E_SET_COLOR_RANGE, value);
            break;
        case 2:
            res = aom_codec_control(&codec_ctx, AV1E_SET_S_FRAME_MODE, value);
            break;
        case 3:
            res = aom_codec_control(&codec_ctx, AV1E_SET_TUNE_CONTENT, value);
            break;
        case 4:
            {
                aom_ext_part_funcs_t part_funcs;
                part_funcs.decision_mode = static_cast<aom_ext_part_decision_mode_t>(value % 2);
                res = aom_codec_control(&codec_ctx, AV1E_SET_EXTERNAL_PARTITION, &part_funcs);
            }
            break;
        case 5:
            {
                int width = value % 65536;
                int height = (value / 65536) % 65536;
                res = aom_codec_control(&codec_ctx, AV1E_SET_RENDER_SIZE, width, height);
            }
            break;
        default:
            break;
    }

    if (res != AOM_CODEC_OK) {
        std::cerr << "Error: " << codec_ctx.err << std::endl;
    }

    CleanupCodecContext(codec_ctx);

    return 0;
}