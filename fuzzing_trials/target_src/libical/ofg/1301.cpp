#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1301(const uint8_t *data, size_t size) {
    // Initialize the iCalendar component and property
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalproperty *property = icalproperty_new_comment("Sample Comment");

    // Ensure the data is not empty to avoid unnecessary processing
    if (size > 0) {
        // Convert the input data to a string for use in the property
        char *dataStr = (char *)malloc(size + 1);
        if (dataStr != NULL) {
            memcpy(dataStr, data, size);
            dataStr[size] = '\0';

            // Create a new property with the fuzz data
            icalproperty *fuzzProperty = icalproperty_new_comment(dataStr);
            if (fuzzProperty != NULL) {
                // Add the fuzz property to the component
                icalcomponent_add_property(component, fuzzProperty);
            }

            // Free the allocated string
            free(dataStr);
        }
    }

    // Clean up
    icalproperty_free(property);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1301(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
