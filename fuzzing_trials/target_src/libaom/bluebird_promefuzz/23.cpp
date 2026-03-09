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
#include "/src/aom/aom/aom_integer.h"
#include "/src/aom/aom/aom_image.h"
#include "/src/aom/aom/aom_codec.h"
#include "/src/aom/aom/aom_frame_buffer.h"
#include "/src/aom/aom/aom_encoder.h"
#include "/src/aom/aom/aom_external_partition.h"
#include "/src/aom/aom/aom.h"
#include "/src/aom/aom/aomcx.h"
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    // Fuzz aom_obu_type_to_string
    fuzz_aom_obu_type_to_string(Data, Size);

    // Fuzz aom_codec_build_config
    fuzz_aom_codec_build_config();

    return 0;
}