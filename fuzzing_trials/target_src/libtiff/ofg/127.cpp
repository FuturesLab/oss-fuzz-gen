#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Call the function-under-test
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();

    // Iterate over the codecs list to ensure we access the data
    TIFFCodec *current = codecs;
    while (current != NULL && current->name != NULL) {
        // Access codec details to simulate usage
        const char *codecName = current->name;
        uint16_t scheme = current->scheme;

        // Print codec name and scheme for debugging purposes
        (void)codecName; // Suppress unused variable warning
        (void)scheme; // Suppress unused variable warning

        // Move to the next codec
        current++;
    }

    // Note: No need to free codecs as per TIFFGetConfiguredCODECs documentation

    return 0;
}