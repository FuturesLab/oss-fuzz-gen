// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
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
#include <iostream>
#include <cstdint>
#include <cstring>
#include <fstream>
#include "aomdx.h"
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aom_encoder.h"
#include "aom_codec.h"
#include "aomcx.h"
#include "aom_integer.h"
#include "aom_image.h"
#include "aom.h"
#include "aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    aom_codec_enc_cfg_t cfg;
    aom_svc_params_t svc_params;

    // Initialize codec
    if (aom_codec_enc_config_default(iface, &cfg, 0)) {
        return 0;
    }

    if (aom_codec_enc_init(&codec, iface, &cfg, 0)) {
        return 0;
    }

    // Prepare the input data
    int input_value;
    std::memcpy(&input_value, Data, sizeof(int));

    // 1. Fuzz aom_codec_control_typechecked_AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR
    aom_codec_control(&codec, AV1E_SET_MAX_CONSEC_FRAME_DROP_CBR, &input_value);

    // 2. Fuzz aom_codec_control_typechecked_AV1E_SET_S_FRAME_MODE
    aom_codec_control(&codec, AV1E_SET_S_FRAME_MODE, &input_value);

    // 3. Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_OVERLAY
    aom_codec_control(&codec, AV1E_SET_ENABLE_OVERLAY, &input_value);

    // 4. Fuzz aom_codec_control_typechecked_AV1E_SET_QUANTIZER_ONE_PASS
    aom_codec_control(&codec, AV1E_SET_QUANTIZER_ONE_PASS, &input_value);

    // 5. Fuzz aom_codec_control_typechecked_AV1E_SET_SVC_PARAMS
    svc_params.number_spatial_layers = input_value % 3 + 1; // Valid range: [1, 3]
    aom_codec_control(&codec, AV1E_SET_SVC_PARAMS, &svc_params);

    // 6. Fuzz aom_codec_control_typechecked_AV1E_SET_LOOPFILTER_CONTROL
    aom_codec_control(&codec, AV1E_SET_LOOPFILTER_CONTROL, &input_value);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}