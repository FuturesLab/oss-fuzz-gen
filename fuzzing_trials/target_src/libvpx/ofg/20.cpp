#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_decoder.h>

// Ensure the function is wrapped in extern "C" for C++ compatibility
extern "C" {
    vpx_codec_iface_t * vpx_codec_vp8_dx();
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Call the function-under-test
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();

    // Check if the interface is not NULL
    if (iface != NULL) {
        // Additional logic can be added here if needed
    }

    return 0;
}