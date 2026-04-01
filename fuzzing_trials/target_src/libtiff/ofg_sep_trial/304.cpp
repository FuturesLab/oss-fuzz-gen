#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a TIFFCodec object
    if (size < sizeof(TIFFCodec)) {
        return 0;
    }

    // Allocate memory for a TIFFCodec object
    TIFFCodec *codec = (TIFFCodec *)malloc(sizeof(TIFFCodec));
    if (codec == NULL) {
        return 0;
    }

    // Initialize the TIFFCodec object with data
    // Copy data into the codec object, ensuring it doesn't exceed the size
    memcpy(codec, data, sizeof(TIFFCodec));

    // Call the function-under-test with the initialized codec
    TIFFUnRegisterCODEC(codec);

    // Free the allocated memory for the codec
    free(codec);

    return 0;
}