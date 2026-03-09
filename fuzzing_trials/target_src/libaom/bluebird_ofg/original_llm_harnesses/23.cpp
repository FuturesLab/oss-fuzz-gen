#include <stdint.h>
#include <stddef.h>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Declare and initialize the necessary variable
    aom_codec_iface_t *iface = (aom_codec_iface_t *)data;

    // Call the function-under-test
    const char *name = aom_codec_iface_name(iface);

    // Use the result to avoid compiler optimizations removing the call
    if (name != NULL) {
        // Do something with the name, e.g., print or log it
        // Here we just use it in a dummy way
        volatile const char *dummy = name;
        (void)dummy;
    }

    return 0;
}