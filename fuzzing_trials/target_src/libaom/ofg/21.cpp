#include <cstdint>
#include <cstddef>

extern "C" {
    // Include the necessary headers for the function-under-test
    #include <aom/aom_codec.h>
    #include <aom/aomcx.h>  // Include the header where aom_codec_av1_cx is declared
}

// Function signature for the function-under-test
extern "C" const char * aom_codec_iface_name(aom_codec_iface_t *);

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize aom_codec_iface_t pointer
    aom_codec_iface_t *iface = aom_codec_av1_cx();

    // Ensure the iface is not NULL
    if (iface == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *name = aom_codec_iface_name(iface);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (name != NULL) {
        // Do something with the name, like printing or logging
    }

    return 0;
}