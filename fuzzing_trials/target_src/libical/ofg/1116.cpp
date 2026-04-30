#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1116(const uint8_t *data, size_t size) {
    // Initialize two icalcomponent objects
    icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the data is not empty
    if (size > 0) {
        // Create a temporary buffer to hold the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer != NULL) {
            // Copy the input data into the buffer
            memcpy(buffer, data, size);
            buffer[size] = '\0'; // Null-terminate the string

            // Convert the buffer into an icalcomponent
            icalcomponent *tempComponent = icalparser_parse_string(buffer);
            if (tempComponent != NULL) {
                // Add the parsed component as a child to the parent
                icalcomponent_add_component(parent, tempComponent);
            }

            // Free the buffer
            free(buffer);
        }
    }

    // Add the child component to the parent component
    icalcomponent_add_component(parent, child);

    // Clean up
    icalcomponent_free(parent);

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

    LLVMFuzzerTestOneInput_1116(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
