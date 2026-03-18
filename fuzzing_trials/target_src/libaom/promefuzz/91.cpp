// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_enc_config_set at aom_encoder.c:298:17 in aom_encoder.h
// aom_codec_control_typechecked_AOME_SET_ROI_MAP at aomcx.h:1898:1 in aomcx.h
// aom_codec_get_global_headers at aom_encoder.c:281:18 in aom_encoder.h
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
#include <cstdio>
#include <cstring>
#include "aom_integer.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom_frame_buffer.h"
#include "aom_encoder.h"
#include "aom_external_partition.h"
#include "aom.h"
#include "aomcx.h"
#include "aom_decoder.h"
#include "aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(aom_codec_enc_cfg_t)) {
        return 0;
    }

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize encoder configuration
    aom_codec_enc_cfg_t enc_cfg;
    memcpy(&enc_cfg, Data, sizeof(aom_codec_enc_cfg_t));

    // Initialize ROI map
    aom_roi_map_t roi_map;
    memset(&roi_map, 0, sizeof(roi_map));
    roi_map.enabled = 1;
    roi_map.roi_map = (unsigned char*)malloc(Size);
    if (!roi_map.roi_map) {
        return 0;
    }
    memcpy(roi_map.roi_map, Data, Size);

    // Invoke aom_codec_enc_config_set
    aom_codec_err_t res = aom_codec_enc_config_set(&codec_ctx, &enc_cfg);
    if (res != AOM_CODEC_OK) {
        free(roi_map.roi_map);
        return 0;
    }

    // Invoke aom_codec_control_typechecked_AOME_SET_ROI_MAP
    res = aom_codec_control_typechecked_AOME_SET_ROI_MAP(&codec_ctx, AOME_SET_ROI_MAP, &roi_map);
    if (res != AOM_CODEC_OK) {
        free(roi_map.roi_map);
        return 0;
    }

    // Invoke aom_codec_get_global_headers
    aom_fixed_buf_t *global_headers = aom_codec_get_global_headers(&codec_ctx);
    if (global_headers) {
        free(global_headers->buf);
        free(global_headers);
    }

    // Free resources
    free(roi_map.roi_map);

    return 0;
}