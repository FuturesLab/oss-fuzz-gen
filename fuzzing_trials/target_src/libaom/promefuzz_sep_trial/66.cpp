// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AOME_SET_CPUUSED at aomcx.h:1910:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC at aomcx.h:2374:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RATE_DISTRIBUTION_INFO at aomcx.h:2353:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_GET_LUMA_CDEF_STRENGTH at aomcx.h:2356:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT at aomcx.h:1948:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID at aomcx.h:1907:1 in aomcx.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <fstream>
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

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    // Initialize codec context
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    // Use first few bytes of Data as a parameter for the API functions
    int param = *reinterpret_cast<const int*>(Data);

    // Call the target functions with diverse parameters
    aom_codec_control_typechecked_AOME_SET_CPUUSED(&codec, 0, param);
    aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC(&codec, 0, param);
    aom_codec_control_typechecked_AV1E_SET_RATE_DISTRIBUTION_INFO(&codec, 0, reinterpret_cast<const char*>(Data));
    aom_codec_control_typechecked_AV1E_GET_LUMA_CDEF_STRENGTH(&codec, 0, &param);
    aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT(&codec, 0, param);
    aom_codec_control_typechecked_AOME_SET_SPATIAL_LAYER_ID(&codec, 0, param);

    // Cleanup
    aom_codec_destroy(&codec);

    return 0;
}