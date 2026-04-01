#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Call the function-under-test
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();

    // Iterate through the codecs list to ensure all are accessed
    // Since TIFFCodec doesn't have a 'next' member, we assume it's a null-terminated array
    for (TIFFCodec *codec = codecs; codec != nullptr && codec->name != nullptr; ++codec) {
        // Access codec fields
        const char *name = codec->name;
        uint16_t scheme = codec->scheme;

        // Simple operations to use the accessed fields
        if (name != nullptr) {
            // Print codec name and scheme (in a real fuzzing scenario, you might log or verify these)
            printf("Codec Name: %s, Scheme: %u\n", name, scheme);
        }
    }

    // Free the allocated memory for codecs if necessary
    // (Assuming TIFFGetConfiguredCODECs allocates memory that needs to be freed)
    _TIFFfree(codecs);

    return 0;
}