#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "aom/aomdx.h"
#include "aom_external_partition.h"
#include "aom_image.h"
#include "aom_codec.h"
#include "aom.h"
#include "aom_encoder.h"
#include "aom/aom_decoder.h"
#include "aom_frame_buffer.h"
#include "aom_integer.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzzing aom_uleb_encode_fixed_size
    uint64_t value = 0;
    if (Size >= sizeof(value)) {
        value = *reinterpret_cast<const uint64_t*>(Data) % 0xFFFFFFFFFFFFFFFF;
    } else {
        for (size_t i = 0; i < Size; ++i) {
            value |= static_cast<uint64_t>(Data[i]) << (i * 8);
        }
    }

    size_t available = Size;
    size_t pad_to_size = 1 + (value % 9); // Random pad size between 1 and 9
    uint8_t coded_value[9] = {0}; // Max LEB128 size
    size_t coded_size = 0;

    aom_uleb_encode_fixed_size(value, available, pad_to_size, coded_value, &coded_size);

    // Fuzzing aom_uleb_encode
    uint8_t coded_value_var[9] = {0};
    size_t coded_size_var = 0;
    aom_uleb_encode(value, available, coded_value_var, &coded_size_var);

    // Fuzzing aom_uleb_size_in_bytes
    size_t size_needed = aom_uleb_size_in_bytes(value);

    // Fuzzing aom_uleb_decode
    uint64_t decoded_value = 0;
    size_t length = 0;
    aom_uleb_decode(coded_value_var, available, &decoded_value, &length);

    // Fuzzing aom_codec_av1_cx
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    if (iface) {
        // Optionally, you could create a codec context here if needed
    }

    // Cleanup and return
    return 0;
}