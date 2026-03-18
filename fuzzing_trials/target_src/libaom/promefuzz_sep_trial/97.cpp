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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aom_codec.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aomcx.h"
#include "aomdx.h"
#include "aom_external_partition.h"
#include "aom_frame_buffer.h"
#include "aom_image.h"
#include "aom_integer.h"

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Test aom_codec_version_str
    const char *version_str = aom_codec_version_str();
    if (version_str) {
        printf("Version String: %s\n", version_str);
    }

    // Test aom_codec_version
    int version = aom_codec_version();
    printf("Version: %d\n", version);

    // Test aom_codec_version_extra_str
    const char *version_extra_str = aom_codec_version_extra_str();
    if (version_extra_str) {
        printf("Version Extra String: %s\n", version_extra_str);
    }

    // Initialize codec context for control typechecked functions
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (iface == nullptr) {
        return 0;
    }

    aom_codec_err_t res = aom_codec_enc_init(&codec_ctx, iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Test aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC
    // Assuming some valid value for testing
    int drop_rtc = Data[0] % 2;
    res = aom_codec_control(&codec_ctx, AV1E_SET_POSTENCODE_DROP_RTC, drop_rtc);
    if (res != AOM_CODEC_OK) {
        printf("Control AV1E_SET_POSTENCODE_DROP_RTC failed: %d\n", res);
    }

    // Test aom_codec_control_typechecked_AV1E_SET_RATE_DISTRIBUTION_INFO
    // Assuming some valid structure for testing
    void *rate_distribution_info = reinterpret_cast<void*>(const_cast<uint8_t*>(Data));
    res = aom_codec_control(&codec_ctx, AV1E_SET_RATE_DISTRIBUTION_INFO, rate_distribution_info);
    if (res != AOM_CODEC_OK) {
        printf("Control AV1E_SET_RATE_DISTRIBUTION_INFO failed: %d\n", res);
    }

    // Test aom_codec_control_typechecked_AV1E_GET_LUMA_CDEF_STRENGTH
    int luma_cdef_strength;
    res = aom_codec_control(&codec_ctx, AV1E_GET_LUMA_CDEF_STRENGTH, &luma_cdef_strength);
    if (res != AOM_CODEC_OK) {
        printf("Control AV1E_GET_LUMA_CDEF_STRENGTH failed: %d\n", res);
    } else {
        printf("Luma CDEF Strength: %d\n", luma_cdef_strength);
    }

    // Cleanup
    aom_codec_destroy(&codec_ctx);
    
    return 0;
}