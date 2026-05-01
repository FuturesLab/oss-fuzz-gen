#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy

extern "C" {
    // Ensure all C headers and functions are wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *tempData = (char *)malloc(size + 1);
    if (tempData == NULL) {
        return 0;
    }

    // Copy data into the temporary buffer and null-terminate it
    memcpy(tempData, data, size);
    tempData[size] = '\0';

    // Create an icalcomponent from the data
    icalcomponent *component = icalparser_parse_string(tempData);

    // Free the temporary buffer
    free(tempData);

    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent *innerComponent = icalcomponent_get_inner(component);

    // Clean up
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_108(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
