#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {
    #include <string.h> // Include the string.h library for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_1132(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size > 0) {
        // Create a string from the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == NULL) {
            return 0;
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data as an iCalendar component
        icalcomponent *component = icalparser_parse_string(inputData);

        // Check if the component was successfully created
        if (component != NULL) {
            // Use the component in some way to ensure code paths are executed
            icalcomponent_kind kind = icalcomponent_isa(component);
            if (kind != ICAL_NO_COMPONENT) {
                // Do something with the component, like iterating over properties
                for (icalproperty *prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
                     prop != NULL;
                     prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {
                    // Process each property
                    const char *propName = icalproperty_get_x_name(prop);
                    if (propName != NULL) {
                        // Do something with propName, like printing or logging
                    }
                }
            }
            // Clean up
            icalcomponent_free(component);
        }

        // Free the input data as it's no longer needed
        free(inputData);
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

    LLVMFuzzerTestOneInput_1132(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
