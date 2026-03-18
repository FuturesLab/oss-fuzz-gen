#include <stdint.h>
#include <stdlib.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a TIFFCodec
    if (size < sizeof(TIFFCodec)) {
        return 0;
    }

    // Allocate memory for a TIFFCodec
    TIFFCodec *codec = (TIFFCodec *)malloc(sizeof(TIFFCodec));
    if (codec == NULL) {
        return 0;
    }

    // Initialize the TIFFCodec with data from the fuzzer
    codec->name = (const char *)data;  // Use the data as the codec name
    codec->scheme = *(uint16_t *)(data + sizeof(const char *));  // Use part of the data as the scheme

    // Call the function-under-test
    TIFFUnRegisterCODEC(codec);

    // Free the allocated memory
    free(codec);

    return 0;
}