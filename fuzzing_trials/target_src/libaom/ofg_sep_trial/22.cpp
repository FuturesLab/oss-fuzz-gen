#include <stdint.h>
#include <stddef.h>
#include <aom/aom_codec.h>

extern "C" {
    // Function under test
    const char *aom_codec_iface_name(aom_codec_iface_t *);
}

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize the aom_codec_iface_t pointer
    aom_codec_iface_t *iface = (aom_codec_iface_t *)data;

    // Call the function under test
    const char *name = aom_codec_iface_name(iface);

    // Check the result (optional, for debugging purposes)
    if (name != NULL) {
        // Do something with the name, like printing or logging
    }

    return 0;
}