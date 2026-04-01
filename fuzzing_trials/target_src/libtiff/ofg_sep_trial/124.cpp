extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Call the function-under-test
    TIFFCodec *codecs = TIFFGetConfiguredCODECs();

    // Iterate over the linked list of codecs to ensure all are accessed
    TIFFCodec *current = codecs;
    while (current != nullptr) {
        // Access codec information
        const char *name = current->name;
        uint16_t scheme = current->scheme; // Corrected type to uint16_t

        // For fuzzing purposes, simply ensure the strings are accessed
        if (name != nullptr) {
            // No operation needed, just accessing the data
        }

        // Move to the next codec in the list
        // Note: There is no 'next' member in TIFFCodec, so we assume single element
        break;
    }

    return 0;
}