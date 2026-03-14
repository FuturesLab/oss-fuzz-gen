#include <cstdint>
#include <cstddef>
#include <aom/aom_codec.h>

extern "C" {
    #include <aom/aom_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(aom_codec_caps_t)) {
        return 0;
    }

    // Use the data to populate the dummy_iface in some way
    // Here, we simply cast the data to a pointer of the appropriate type
    // This is a simple way to fuzz without knowing the internal structure
    aom_codec_iface_t *iface = reinterpret_cast<aom_codec_iface_t *>(const_cast<uint8_t *>(data));

    // Call the function-under-test
    aom_codec_caps_t caps = aom_codec_get_caps(iface);

    // Optionally, use the result in some way to prevent optimization out
    (void)caps;

    return 0;
}