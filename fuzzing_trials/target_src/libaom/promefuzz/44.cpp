// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_CPUUSED at aomcx.h:1910:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD at aomcx.h:1919:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF at aomcx.h:1913:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT at aomcx.h:1948:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_CQ_LEVEL at aomcx.h:1937:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT at aomcx.h:1940:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 6) return 0;

    int cpu_used = *reinterpret_cast<const int*>(Data);
    int static_threshold = *reinterpret_cast<const int*>(Data + sizeof(int));
    int enable_auto_alt_ref = *reinterpret_cast<const int*>(Data + sizeof(int) * 2);
    int max_inter_bitrate_pct = *reinterpret_cast<const int*>(Data + sizeof(int) * 3);
    int cq_level = *reinterpret_cast<const int*>(Data + sizeof(int) * 4);
    int max_intra_bitrate_pct = *reinterpret_cast<const int*>(Data + sizeof(int) * 5);

    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    // Assuming the codec interface is initialized properly
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (!iface) return 0;

    codec.iface = iface;

    // Fuzz aom_codec_control_typechecked_AOME_SET_CPUUSED
    aom_codec_control_typechecked_AOME_SET_CPUUSED(&codec, 0, cpu_used);

    // Fuzz aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD
    aom_codec_control_typechecked_AOME_SET_STATIC_THRESHOLD(&codec, 0, static_threshold);

    // Fuzz aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF
    aom_codec_control_typechecked_AOME_SET_ENABLEAUTOALTREF(&codec, 0, enable_auto_alt_ref);

    // Fuzz aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT
    aom_codec_control_typechecked_AOME_SET_MAX_INTER_BITRATE_PCT(&codec, 0, max_inter_bitrate_pct);

    // Fuzz aom_codec_control_typechecked_AOME_SET_CQ_LEVEL
    aom_codec_control_typechecked_AOME_SET_CQ_LEVEL(&codec, 0, cq_level);

    // Fuzz aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT
    aom_codec_control_typechecked_AOME_SET_MAX_INTRA_BITRATE_PCT(&codec, 0, max_intra_bitrate_pct);

    return 0;
}