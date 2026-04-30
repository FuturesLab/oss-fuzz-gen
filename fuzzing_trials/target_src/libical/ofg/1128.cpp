#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>  // Include the correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_1128(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = NULL;

    // Ensure size is sufficient to create a component
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            return 0; // Exit if memory allocation fails
        }

        // Copy data into buffer and null-terminate it
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Parse the data into an icalcomponent
        component = icalparser_parse_string(buffer);

        // Free the buffer
        free(buffer);

        // If the component is successfully created, call the function-under-test
        if (component != NULL) {
            icalcomponent_convert_errors(component);

            // Clean up
            icalcomponent_free(component);
        }
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

    LLVMFuzzerTestOneInput_1128(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
