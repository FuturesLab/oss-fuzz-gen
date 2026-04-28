#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_753(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = new char[size + 1];
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Convert the input data to an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Call the function-under-test
    if (component != nullptr) {
        char *location = icaltimezone_get_location_from_vtimezone(component);

        // Free the location string if it was allocated
        if (location != nullptr) {
            icalmemory_free_buffer(location);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Clean up
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_753(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
