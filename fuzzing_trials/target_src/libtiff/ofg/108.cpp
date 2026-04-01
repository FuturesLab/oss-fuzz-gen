#include <cstdint>
#include <cstdio>
#include <cstring>

extern "C" {
    // Assuming the function is defined in a TIFF library, include necessary headers
    #include <tiffio.h>
}

// Define a dummy handler function to pass as the third parameter
void dummyHandler() {
    // This function intentionally left blank
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating meaningful strings
    if (size < 2) {
        return 0;
    }

    // Split the data into two parts for the two string parameters
    size_t halfSize = size / 2;
    char *name = new char[halfSize + 1];
    char *message = new char[size - halfSize + 1];

    // Copy data into the strings and null-terminate them
    std::memcpy(name, data, halfSize);
    name[halfSize] = '\0';

    std::memcpy(message, data + halfSize, size - halfSize);
    message[size - halfSize] = '\0';

    // Call the function-under-test
    TIFFError(name, message, (void*)dummyHandler);

    // Clean up
    delete[] name;
    delete[] message;

    return 0;
}