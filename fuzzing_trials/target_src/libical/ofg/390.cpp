#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_390(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data as a string
    char *inputData = static_cast<char *>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0; // Failed to allocate memory
    }

    // Copy the input data and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // If parsing was successful, call the function-under-test
    if (component != nullptr) {
        const char *description = icalcomponent_get_description(component);

        // Optionally, use the description here
        (void)description;

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated input data buffer
    free(inputData);

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

    LLVMFuzzerTestOneInput_390(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
