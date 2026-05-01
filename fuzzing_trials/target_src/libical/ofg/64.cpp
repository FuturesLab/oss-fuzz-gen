#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent and icalproperty_kind
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalproperty_kind kind = ICAL_ANY_PROPERTY;

    // Ensure that the data is not empty
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            return 0; // Exit if memory allocation fails
        }

        // Copy the data into the buffer and null-terminate it
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Try to parse the buffer into an icalcomponent
        icalcomponent *parsed_component = icalparser_parse_string(buffer);
        if (parsed_component != NULL) {
            // If parsing is successful, replace the initial component
            icalcomponent_free(component);
            component = parsed_component;
        }

        // Free the buffer
        free(buffer);
    }

    // Call the function-under-test
    icalproperty *property = icalcomponent_get_next_property(component, kind);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
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

    LLVMFuzzerTestOneInput_64(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
