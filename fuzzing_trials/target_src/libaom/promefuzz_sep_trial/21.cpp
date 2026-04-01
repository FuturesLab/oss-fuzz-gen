// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC at aomcx.h:2374:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE at aomcx.h:2173:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC at aomcx.h:2326:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SUPERBLOCK_SIZE at aomcx.h:2031:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES at aomcx.h:2167:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE at aomcx.h:2043:1 in aomcx.h
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
#include <fstream>
#include <cstdint>
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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) {
        return 0;
    }

    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    int control_value = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    int control_id = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC
    aom_codec_control_typechecked_AV1E_SET_POSTENCODE_DROP_RTC(&codec_ctx, control_id, control_value);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE
    if (Size >= sizeof(int)) {
        int enable_palette = *reinterpret_cast<const int*>(Data);
        aom_codec_control_typechecked_AV1E_SET_ENABLE_PALETTE(&codec_ctx, control_id, enable_palette);
        Data += sizeof(int);
        Size -= sizeof(int);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC
    if (Size >= sizeof(int)) {
        int rtc_external_rc = *reinterpret_cast<const int*>(Data);
        aom_codec_control_typechecked_AV1E_SET_RTC_EXTERNAL_RC(&codec_ctx, control_id, rtc_external_rc);
        Data += sizeof(int);
        Size -= sizeof(int);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SUPERBLOCK_SIZE
    if (Size >= sizeof(unsigned int)) {
        unsigned int superblock_size = *reinterpret_cast<const unsigned int*>(Data);
        aom_codec_control_typechecked_AV1E_SET_SUPERBLOCK_SIZE(&codec_ctx, control_id, superblock_size);
        Data += sizeof(unsigned int);
        Size -= sizeof(unsigned int);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES
    if (Size >= sizeof(int)) {
        int enable_superres = *reinterpret_cast<const int*>(Data);
        aom_codec_control_typechecked_AV1E_SET_ENABLE_SUPERRES(&codec_ctx, control_id, enable_superres);
        Data += sizeof(int);
        Size -= sizeof(int);
    }

    // Fuzz aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE
    if (Size >= sizeof(int)) {
        int force_video_mode = *reinterpret_cast<const int*>(Data);
        aom_codec_control_typechecked_AV1E_SET_FORCE_VIDEO_MODE(&codec_ctx, control_id, force_video_mode);
    }

    return 0;
}