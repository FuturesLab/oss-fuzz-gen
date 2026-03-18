// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION at aomcx.h:2007:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT at aomcx.h:1992:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH at aomcx.h:2305:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA at aomcx.h:2302:1 in aomcx.h
// aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE at aomcx.h:2383:1 in aomcx.h
// aom_codec_control_typechecked_AOME_SET_CPUUSED at aomcx.h:1910:1 in aomcx.h
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));
    codec.iface = aom_codec_av1_cx();

    int param = *(reinterpret_cast<const int*>(Data));

    // Each control function requires a control ID, which is typically defined in aomcx.h
    // Assuming these are the correct control IDs
    const int AV1E_SET_CHROMA_SAMPLE_POSITION = 1;
    const int AV1E_SET_TUNE_CONTENT = 2;
    const int AV1E_SET_ENABLE_TX_SIZE_SEARCH = 3;
    const int AV1E_SET_ENABLE_DIRECTIONAL_INTRA = 4;
    const int AV1E_SET_SCREEN_CONTENT_DETECTION_MODE = 5;
    const int AOME_SET_CPUUSED = 6;

    // Fuzz aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION
    aom_codec_control_typechecked_AV1E_SET_CHROMA_SAMPLE_POSITION(&codec, AV1E_SET_CHROMA_SAMPLE_POSITION, param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT
    aom_codec_control_typechecked_AV1E_SET_TUNE_CONTENT(&codec, AV1E_SET_TUNE_CONTENT, param);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH
    aom_codec_control_typechecked_AV1E_SET_ENABLE_TX_SIZE_SEARCH(&codec, AV1E_SET_ENABLE_TX_SIZE_SEARCH, param % 2);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA
    aom_codec_control_typechecked_AV1E_SET_ENABLE_DIRECTIONAL_INTRA(&codec, AV1E_SET_ENABLE_DIRECTIONAL_INTRA, param % 2);

    // Fuzz aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE
    aom_codec_control_typechecked_AV1E_SET_SCREEN_CONTENT_DETECTION_MODE(&codec, AV1E_SET_SCREEN_CONTENT_DETECTION_MODE, param % 2);

    // Fuzz aom_codec_control_typechecked_AOME_SET_CPUUSED
    aom_codec_control_typechecked_AOME_SET_CPUUSED(&codec, AOME_SET_CPUUSED, param);

    return 0;
}