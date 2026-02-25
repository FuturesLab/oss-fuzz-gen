// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
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

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Ensure we have enough data

    // Prepare codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Get AV1 codec interface
    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) return 0;

    // Parse input data
    int width = (Data[0] % 1920) + 1; // Random width between 1 and 1920
    int height = (Data[1] % 1080) + 1; // Random height between 1 and 1080
    res = aom_codec_control(&codec_ctx, AV1E_SET_RENDER_SIZE, width, height);
    
    // Check return value
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Test other controls with random values
    res = aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_PALETTE, Data[2] % 2);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    res = aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_CFL_INTRA, Data[3] % 2);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Set SVC parameters
    aom_svc_params_t svc_params;
    svc_params.number_spatial_layers = Data[4] % AOM_MAX_SS_LAYERS + 1;
    memset(svc_params.max_quantizers, 0, sizeof(svc_params.max_quantizers));
    memset(svc_params.scaling_factor_num, 0, sizeof(svc_params.scaling_factor_num));
    memset(svc_params.framerate_factor, 0, sizeof(svc_params.framerate_factor));
    
    res = aom_codec_control(&codec_ctx, AV1E_SET_SVC_PARAMS, &svc_params);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    return 0;
}