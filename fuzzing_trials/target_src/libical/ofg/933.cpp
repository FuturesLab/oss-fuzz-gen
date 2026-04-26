#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalproperty.h>
    #include <libical/icalparser.h>
}

extern "C" int LLVMFuzzerTestOneInput_933(const uint8_t *data, size_t size) {
    // Check if the input data is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_string = (char *)malloc(size + 1);
    if (!input_string) {
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Parse the input string as an iCalendar component
    icalcomponent *comp = icalparser_parse_string(input_string);
    if (comp == NULL) {
        free(input_string);
        return 0;
    }

    // Iterate through the properties of the component
    icalproperty *prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
    while (prop != NULL) {
        // Perform some operations on the properties
        const char *prop_name = icalproperty_get_property_name(prop);
        if (strcmp(prop_name, "SUMMARY") == 0) {
            const char *summary = icalproperty_get_summary(prop);
            if (summary) {
                // Do something with the summary
            }
        }
        prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY);
    }

    // Clean up
    icalcomponent_free(comp);
    free(input_string);

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

    LLVMFuzzerTestOneInput_933(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
