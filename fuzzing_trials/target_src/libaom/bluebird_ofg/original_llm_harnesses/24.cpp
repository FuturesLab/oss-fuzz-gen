#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure we have enough data to perform meaningful operations
    if (size < sizeof(void *)) {
        return 0;
    }

    // Cast the input data to a pointer of type aom_codec_iface_t
    aom_codec_iface_t *iface = reinterpret_cast<aom_codec_iface_t *>(const_cast<uint8_t *>(data));

    // Call the function-under-test
    const char *iface_name = aom_codec_iface_name(iface);

    // The result can be used for further checks or logging if needed
    // For now, we simply call the function to ensure it executes
    (void)iface_name; // Suppress unused variable warning

    return 0;
}