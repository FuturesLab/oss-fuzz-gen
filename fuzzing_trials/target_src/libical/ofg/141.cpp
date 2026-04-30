#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> // Include for malloc and free
#include <string.h> // Include for memcpy

extern "C" {
    // Ensure all C headers and functions are wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);
    if (component != NULL) {
        // Call the function-under-test
        const char *location = icalcomponent_get_location(component);

        // Print the location if it's not NULL
        if (location != NULL) {
            printf("Location: %s\n", location);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_141(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
