extern "C" {
    #include <tiffio.h>
}

#include <cstdint>
#include <cstring>

// Define a simple TIFFInitMethod function with the correct signature
int dummyInitMethod(TIFF *tiff, int scheme) {
    // This is a dummy implementation for the purpose of fuzzing
    return 1;
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < 3) {
        return 0;
    }

    // Extract a uint16_t value from the data
    uint16_t scheme = (data[0] << 8) | data[1];

    // Use the rest of the data as a string for the name
    size_t nameLength = size - 2;
    char *name = new char[nameLength + 1];
    memcpy(name, data + 2, nameLength);
    name[nameLength] = '\0'; // Null-terminate the string

    // Call the function-under-test
    TIFFCodec *codec = TIFFRegisterCODEC(scheme, name, dummyInitMethod);

    // Clean up
    delete[] name;

    return 0;
}