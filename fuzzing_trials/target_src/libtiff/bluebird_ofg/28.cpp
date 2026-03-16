#include "tiffio.h"
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Call the function-under-test
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();

    // Iterate over the codecs to ensure they are accessed
    for (TIFFCodec *codec = codecs; codec->name != nullptr; ++codec) {
        // Access codec properties to simulate usage
        const char *name = codec->name;
        uint16_t scheme = codec->scheme;

        // Print codec information (optional, for debugging purposes)
        // printf("Codec Name: %s, Scheme: %u\n", name, scheme);
    }

    // Free the codecs list if necessary
    if (codecs != nullptr) {
        _TIFFfree(codecs);
    }

    return 0;
}