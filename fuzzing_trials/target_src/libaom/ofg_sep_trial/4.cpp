#include <cstdint>
#include <cstdlib>
#include <aom/aom_codec.h>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure size is at least the size of aom_codec_iface_t pointer
    if (size < sizeof(aom_codec_iface_t *)) {
        return 0;
    }

    // Create a dummy aom_codec_iface_t pointer from the input data
    aom_codec_iface_t *iface = reinterpret_cast<aom_codec_iface_t *>(const_cast<uint8_t *>(data));

    // Call the function under test
    aom_codec_caps_t caps = aom_codec_get_caps(iface);

    // Use the result in some way to prevent compiler optimizations from removing the call
    volatile aom_codec_caps_t volatile_caps = caps;
    (void)volatile_caps;

    return 0;
}