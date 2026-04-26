#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

// Wrap the necessary includes and code in extern "C" to ensure C linkage
extern "C" {
    #include "libical/ical.h" // Correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_508(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *inputData = new char[size + 1];
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the buffer

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    delete[] inputData;

    if (component != NULL) {
        // Call the function-under-test
        icalproperty_status status = icalcomponent_get_status(component);

        // Clean up the component
        icalcomponent_free(component);
    }

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

    LLVMFuzzerTestOneInput_508(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
