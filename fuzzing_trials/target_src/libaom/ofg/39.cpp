#include <stdint.h>
#include <stdlib.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aom_encoder.h>

extern "C" {

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure the size is reasonable for creating a codec interface
    if (size < sizeof(aom_codec_iface_t *)) {
        return 0; // Not enough data to create a valid interface
    }

    // Create a codec interface pointer from the input data
    aom_codec_iface_t *iface = (aom_codec_iface_t *)(uintptr_t)(*(uint64_t *)data);

    // Call the function under test
    aom_codec_caps_t caps = aom_codec_get_caps(iface);

    // We can perform some checks on the caps if needed, but since this is fuzzing,
    // we are primarily interested in executing the function.

    return 0;
}

} // extern "C"