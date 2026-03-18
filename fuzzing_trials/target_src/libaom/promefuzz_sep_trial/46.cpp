// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
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
#include <cstring>
#include <iostream>
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    aom_codec_iface_t *iface = aom_codec_av1_cx();  // Assume using AV1 encoder
    codec_ctx.iface = iface;

    // Initialize codec
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;  // Initialization failed, exit early
    }

    // Randomly choose a function to fuzz
    switch (Data[0] % 5) {
        case 0: {
            // Fuzz aom_codec_destroy
            res = aom_codec_destroy(&codec_ctx);
            break;
        }
        case 1: {
            // Fuzz aom_codec_control_typechecked_AOME_SET_ARNR_STRENGTH
            int strength = Data[1] % 16;  // Random strength value
            res = aom_codec_control(&codec_ctx, AOME_SET_ARNR_STRENGTH, strength);
            break;
        }
        case 2: {
            // Fuzz aom_codec_control_typechecked_AOME_SET_ROI_MAP
            aom_roi_map_t roi_map;
            memset(&roi_map, 0, sizeof(roi_map));
            roi_map.enabled = Data[1] % 2;
            res = aom_codec_control(&codec_ctx, AOME_SET_ROI_MAP, &roi_map);
            break;
        }
        case 3: {
            // Fuzz aom_codec_control_typechecked_AOME_SET_SCALEMODE
            aom_scaling_mode_t scale_mode;
            memset(&scale_mode, 0, sizeof(scale_mode));
            scale_mode.h_scaling_mode = static_cast<AOM_SCALING_MODE>(Data[1] % 9);
            res = aom_codec_control(&codec_ctx, AOME_SET_SCALEMODE, &scale_mode);
            break;
        }
        case 4: {
            // Fuzz aom_codec_set_option
            const char *option_name = "dummy_option";
            const char *option_value = "dummy_value";
            res = aom_codec_set_option(&codec_ctx, option_name, option_value);
            break;
        }
    }

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}