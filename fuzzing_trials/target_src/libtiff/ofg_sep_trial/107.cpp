#include <tiffio.h>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    // Declare the function-under-test
    TIFFCodec * TIFFRegisterCODEC(uint16_t scheme, const char *name, int (*init)(TIFF*, int));
}

// Dummy initialization method for the codec
int DummyTIFFInitMethod(TIFF *tiff, int value) {
    // This is a stub function for testing purposes
    return 1; // Return success
}

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < 3) return 0; // Need at least 3 bytes for scheme and name

    // Extract a 16-bit scheme value from the input data
    uint16_t scheme = (data[0] << 8) | data[1];

    // Extract a name from the input data
    const char *name = reinterpret_cast<const char*>(data + 2);

    // Ensure the name is null-terminated
    size_t name_length = strnlen(name, size - 2);
    char *name_copy = static_cast<char*>(malloc(name_length + 1));
    if (name_copy == nullptr) return 0; // Allocation failed
    memcpy(name_copy, name, name_length);
    name_copy[name_length] = '\0';

    // Call the function-under-test
    TIFFCodec *codec = TIFFRegisterCODEC(scheme, name_copy, DummyTIFFInitMethod);

    // Clean up
    free(name_copy);

    return 0;
}