#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Create a string from the input data to use with libical functions
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Memory allocation failed, return early
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);

    // If parsing was successful, explore further with the component
    if (component != NULL) {
        // Example: Iterate over properties or components
        icalproperty *prop;
        for (prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
             prop != NULL;
             prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {
            // Just access the property name to simulate some processing
            const char *propName = icalproperty_get_property_name(prop);
        }

        // Clean up the created component
        icalcomponent_free(component);
    }

    // Free the allocated input string
    free(input);

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

    LLVMFuzzerTestOneInput_49(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
