#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_1148(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a dummy icalproperty
    icalproperty *property = icalproperty_new(ICAL_COMMENT_PROPERTY);

    // Use the data to set a value in the property
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    // Set the value to the property
    icalproperty_set_comment(property, value);

    // Call the function-under-test
    // Instead of just getting the status, let's perform more operations
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_property(component, property);

    // Serialize the component to a string and parse it back
    char *component_str = icalcomponent_as_ical_string(component);
    icalcomponent *parsed_component = icalparser_parse_string(component_str);

    // Clean up
    free(value);
    free(component_str);
    icalcomponent_free(parsed_component);
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

    LLVMFuzzerTestOneInput_1148(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
