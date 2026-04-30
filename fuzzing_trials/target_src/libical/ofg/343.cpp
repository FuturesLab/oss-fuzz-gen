#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
    // Ensure that there is at least one byte for the string
    if (size < 1) return 0;

    // Create a null-terminated string from the input data
    char *prodid = (char *)malloc(size + 1);
    if (prodid == NULL) return 0;
    memcpy(prodid, data, size);
    prodid[size] = '\0';

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_PRODID_PROPERTY);
    if (property == NULL) {
        free(prodid);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_prodid(property, prodid);

    // Additional operations to increase code coverage
    const char *retrieved_prodid = icalproperty_get_prodid(property);
    if (retrieved_prodid != NULL) {
        // Compare the set and retrieved values
        if (strcmp(prodid, retrieved_prodid) != 0) {
            // Handle the mismatch case if necessary
        }
    }

    // Attempt to parse the prodid to ensure it is utilized
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component != NULL) {
        icalcomponent_add_property(component, property);

        // Serialize and parse back to increase coverage
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            icalcomponent *parsed_component = icalparser_parse_string(str);
            if (parsed_component != NULL) {
                icalcomponent_free(parsed_component);
            }
            free(str);
        }

        icalcomponent_free(component);
    } else {
        // Clean up the property if the component creation fails
        icalproperty_free(property);
    }

    free(prodid);

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

    LLVMFuzzerTestOneInput_343(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
