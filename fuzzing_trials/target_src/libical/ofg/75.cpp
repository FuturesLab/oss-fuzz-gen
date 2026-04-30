#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Initialize the icalcomponent and icalproperty_kind
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty_kind kind = ICAL_ANY_PROPERTY;

    // Add some properties to the component to ensure it is not empty
    icalproperty *summary = icalproperty_new_summary("Sample Summary");
    icalcomponent_add_property(component, summary);

    icalproperty *description = icalproperty_new_description("Sample Description");
    icalcomponent_add_property(component, description);

    // Use the input data to modify the component or properties
    // For example, create a new property from the input data
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0'; // Null-terminate the string

    icalproperty *custom_property = icalproperty_new_comment(data_copy);
    icalcomponent_add_property(component, custom_property);

    // Call the function under test
    icalproperty *property = icalcomponent_get_first_property(component, kind);

    // Process the component to increase code coverage
    char *component_as_string = icalcomponent_as_ical_string(component);
    if (component_as_string) {
        // Optionally, you can print or log the string for debugging
        // printf("%s\n", component_as_string);
    }

    // Clean up
    free(data_copy);
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

    LLVMFuzzerTestOneInput_75(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
