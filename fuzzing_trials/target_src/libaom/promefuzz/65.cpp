// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_enc_config_default at aom_encoder.c:100:17 in aom_encoder.h
// aom_codec_enc_init_ver at aom_encoder.c:38:17 in aom_encoder.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_CDEF at aomcx.h:2037:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING at aomcx.h:2341:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_QM at aomcx.h:2052:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP at aomcx.h:2344:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING at aomcx.h:1974:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC at aomcx.h:2046:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bool)) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec interface
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) return 0;

    // Initialize encoder configuration
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) return 0;

    // Initialize the codec
    if (aom_codec_enc_init(&codec_ctx, iface, &cfg, 0) != AOM_CODEC_OK) return 0;

    // Prepare a boolean value from the input data
    bool enable_feature = Data[0] % 2;

    // Define control IDs
    int control_id_cdef = AV1E_SET_ENABLE_CDEF;
    int control_id_skip_postproc = AV1E_SET_SKIP_POSTPROC_FILTERING;
    int control_id_enable_qm = AV1E_SET_ENABLE_QM;
    int control_id_sb_qp_sweep = AV1E_ENABLE_SB_QP_SWEEP;
    int control_id_frame_parallel = AV1E_SET_FRAME_PARALLEL_DECODING;
    int control_id_enable_obmc = AV1E_SET_ENABLE_OBMC;

    // Invoke the target functions with the codec context and boolean value
    aom_codec_control_typechecked_AV1E_SET_ENABLE_CDEF(&codec_ctx, control_id_cdef, enable_feature);
    aom_codec_control_typechecked_AV1E_SET_SKIP_POSTPROC_FILTERING(&codec_ctx, control_id_skip_postproc, enable_feature);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_QM(&codec_ctx, control_id_enable_qm, enable_feature);
    aom_codec_control_typechecked_AV1E_ENABLE_SB_QP_SWEEP(&codec_ctx, control_id_sb_qp_sweep, enable_feature);
    aom_codec_control_typechecked_AV1E_SET_FRAME_PARALLEL_DECODING(&codec_ctx, control_id_frame_parallel, enable_feature);
    aom_codec_control_typechecked_AV1E_SET_ENABLE_OBMC(&codec_ctx, control_id_enable_obmc, enable_feature);

    // Cleanup codec context
    if (aom_codec_destroy(&codec_ctx) != AOM_CODEC_OK) {
        fprintf(stderr, "Failed to destroy codec\n");
    }

    return 0;
}