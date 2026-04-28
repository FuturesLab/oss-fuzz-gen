#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1043(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely use it as a C-string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the string

    // Call the function-under-test with the null-terminated data
    // Ensure the input data is not empty to increase code coverage
    if (size > 0) {
        // Attempt to parse the data as an iCalendar component
        icalcomponent *comp = icalparser_parse_string(null_terminated_data);

        // Check if parsing was successful
        if (comp != NULL) {
            // Iterate over properties in the component to increase coverage
            for (icalproperty *prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
                 prop != NULL;
                 prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY)) {
                // Perform some operation on each property
                const char *prop_name = icalproperty_get_name(prop);
                if (prop_name != NULL) {
                    // Just a dummy operation to use the property name
                    (void)strlen(prop_name);
                }
            }
            // Clean up
            icalcomponent_free(comp);
        }
    }
    
    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_1043(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
