#include <stdint.h>
#include <stddef.h>
#include <aom/aom_decoder.h>

extern "C" {
    // Function prototype from the library
    aom_codec_iface_t * aom_codec_av1_dx();
}

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Call the function-under-test
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Check if the interface pointer is not NULL
    if (iface != NULL) {
        // Optionally, you can perform further operations or checks on the returned interface
        // For now, we just ensure the function is called and the result is not NULL
    }

    return 0;
}