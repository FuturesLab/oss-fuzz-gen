#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
    // Initialize the library
    icaltimezone *timezone = icaltimezone_new();
    icalcomponent *component = icalcomponent_new(ICAL_VTIMEZONE_COMPONENT);

    // Ensure data is not empty and size is reasonable for our use
    if (size > 0 && size < 1024) {
        // Create a temporary buffer to hold the data
        char *buffer = (char *)malloc(size + 1);
        if (buffer != NULL) {
            // Copy the data into the buffer and null-terminate it
            memcpy(buffer, data, size);
            buffer[size] = '\0';

            // Parse the buffer into an icalcomponent
            icalcomponent *parsed_component = icalparser_parse_string(buffer);
            if (parsed_component != NULL) {
                // Set the parsed component to the timezone
                icaltimezone_set_component(timezone, parsed_component);

                // Free the parsed component
                icalcomponent_free(parsed_component);
            }

            // Free the buffer
            free(buffer);
        }
    }

    // Clean up
    icalcomponent_free(component);
    icaltimezone_free(timezone, 1);

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

    LLVMFuzzerTestOneInput_263(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
