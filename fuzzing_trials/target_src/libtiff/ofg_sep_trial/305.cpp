#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a TIFFCodec object
    if (size < sizeof(TIFFCodec)) {
        return 0;
    }

    // Create a TIFFCodec object from the input data
    TIFFCodec *codec = (TIFFCodec *)data;

    // Call the function-under-test
    TIFFUnRegisterCODEC(codec);

    return 0;
}