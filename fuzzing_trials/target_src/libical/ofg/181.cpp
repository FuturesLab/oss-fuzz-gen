#include <cstdint> // Include standard library for uint8_t
#include <cstddef> // Include standard library for size_t
#include <cstring> // Include standard library for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    // Create a string from the input data
    char *inputData = new char[size + 1];
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Clean up
    if (component != nullptr) {
        icalcomponent_free(component);
    }
    delete[] inputData;

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_181(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
