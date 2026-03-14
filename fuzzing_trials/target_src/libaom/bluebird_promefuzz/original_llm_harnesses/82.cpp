// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_obu_type_to_string at aom_codec.c:186:13 in aom_codec.h
// aom_codec_build_config at aom_config.c:13:13 in aom_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
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
}

#include <cstdint>
#include <cstring>
#include <fstream>

static void fuzz_aom_obu_type_to_string(const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Ensure there is enough data
    OBU_TYPE type = static_cast<OBU_TYPE>(Data[0]); // Use the first byte as OBU_TYPE
    const char *result = aom_obu_type_to_string(type);
    (void)result; // Use the result to avoid unused variable warning
}

static void fuzz_aom_codec_build_config() {
    const char *config = aom_codec_build_config();
    (void)config; // Use the result to avoid unused variable warning
}

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    // Fuzz aom_obu_type_to_string
    fuzz_aom_obu_type_to_string(Data, Size);

    // Fuzz aom_codec_build_config
    fuzz_aom_codec_build_config();

    return 0;
}