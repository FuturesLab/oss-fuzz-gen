#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    if (size < sizeof(uint16_t)) {
        return 0; // Not enough data to form a uint16_t
    }

    // Extract a uint16_t value from the input data
    uint16_t codec_id = *(reinterpret_cast<const uint16_t*>(data));

    // Call the function-under-test
    const TIFFCodec *codec = TIFFFindCODEC(codec_id);

    // The function returns a pointer, but we don't need to do anything with it
    // for the purpose of fuzzing. We just ensure the function is called.

    return 0;
}