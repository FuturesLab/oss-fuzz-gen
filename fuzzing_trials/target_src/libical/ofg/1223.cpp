#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1223(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL and has a size greater than 0
    if (data != NULL && size > 0) {
        // Convert the input data to a string
        char *inputStr = (char *)malloc(size + 1);
        if (inputStr != NULL) {
            memcpy(inputStr, data, size);
            inputStr[size] = '\0';

            // Attempt to parse the input string as an iCalendar component
            icalcomponent *comp = icalparser_parse_string(inputStr);
            if (comp != NULL) {
                // Iterate over properties in the component
                icalproperty *prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
                while (prop != NULL) {
                    // Retrieve and use the property name and value
                    const char *propName = icalproperty_get_property_name(prop);
                    const char *propValue = icalproperty_get_comment(prop);

                    // For fuzzing, we can print or log the property name and value
                    // printf("Property Name: %s, Property Value: %s\n", propName, propValue);

                    // Move to the next property
                    prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY);
                }
                // Free the parsed component
                icalcomponent_free(comp);
            }

            // Free the allocated string
            free(inputStr);
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

    LLVMFuzzerTestOneInput_1223(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
