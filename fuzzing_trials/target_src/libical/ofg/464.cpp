#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_464(const uint8_t *data, size_t size) {
    // Initialize the iCalendar parser
    icalcomponent *component = NULL;
    icalproperty_kind kind = ICAL_ANY_PROPERTY;

    if (size > 0) {
        // Create a temporary buffer to hold the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == NULL) {
            return 0;
        }

        // Copy the input data to the buffer and null-terminate it
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data into an icalcomponent
        component = icalparser_parse_string(inputData);

        // Free the temporary buffer
        free(inputData);
    }

    if (component != NULL) {
        // Fuzz the icalcomponent_get_next_property function
        icalproperty *property = icalcomponent_get_next_property(component, kind);

        // Do something with the property to avoid compiler optimizations
        if (property != NULL) {
            // For example, get the property name
            const char *propName = icalproperty_get_property_name(property);
            (void)propName; // Use the property name in some way
        }

        // Free the component after use
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

    LLVMFuzzerTestOneInput_464(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
