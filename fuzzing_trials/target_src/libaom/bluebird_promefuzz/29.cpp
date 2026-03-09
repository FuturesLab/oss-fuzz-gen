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
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aomcx.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Prepare environment
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    codec.iface = aom_codec_av1_cx();
    codec.name = "av1";

    // Use a portion of the input data as an integer parameter
    int param = 0;
    memcpy(&param, Data, sizeof(int));

    // Fuzz aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC
    aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC(&codec, AV1E_SET_POSTENCODE_DROP_RTC, param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_RATE_DISTRIBUTION_INFO
    aom_codec_control_typechecked_AV1E_SET_RATE_DISTRIBUTION_INFO(&codec, AV1E_SET_RATE_DISTRIBUTION_INFO, reinterpret_cast<const char*>(Data));

    // Fuzz aom_codec_control_typechecked_AV1E_GET_LUMA_CDEF_STRENGTH
    int luma_strength;
    aom_codec_control_typechecked_AV1E_GET_LUMA_CDEF_STRENGTH(&codec, AV1E_GET_LUMA_CDEF_STRENGTH, &luma_strength);

    // Call aom_codec_version_str
    const char *version_str = aom_codec_version_str();
    if (version_str) {
        printf("Version: %s\n", version_str);
    }

    // Call aom_codec_version_extra_str
    const char *version_extra_str = aom_codec_version_extra_str();
    if (version_extra_str) {
        printf("Version Extra: %s\n", version_extra_str);
    }

    // Call aom_codec_version
    int version = aom_codec_version();
    printf("Version (int): %d\n", version);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}