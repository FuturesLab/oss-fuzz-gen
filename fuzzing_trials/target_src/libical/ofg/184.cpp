#include <cstdint> // For uint8_t
#include <cstddef> // For size_t
#include <cstring> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

// Ensure that the fuzz target is compatible with C code
extern "C" int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    // Ensure that we have enough bytes to interpret as icalproperty_xlicclass
    if (size < 2) {
        return 0;
    }

    // Use the first byte of data to determine the xlicclass value
    icalproperty_xlicclass xlicclass = static_cast<icalproperty_xlicclass>(data[0] % (ICAL_XLICCLASS_NONE + 1));

    // Use the remaining bytes of data to create a string for testing
    const char *xlicclass_string = nullptr;
    if (size > 2) {
        // Allocate memory for the string and copy data into it
        char *buffer = new char[size - 1];
        memcpy(buffer, data + 1, size - 1);
        buffer[size - 2] = '\0'; // Ensure null-termination
        xlicclass_string = buffer;
    }

    // Call the function-under-test with more complex input
    icalproperty *property = icalproperty_vanew_xlicclass(xlicclass, xlicclass_string, nullptr);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    delete[] xlicclass_string;

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_184(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
