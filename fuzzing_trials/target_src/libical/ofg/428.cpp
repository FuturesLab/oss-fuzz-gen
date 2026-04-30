#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_428(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_summary("Sample Summary");

    // Ensure the component and property are not NULL
    if (component == NULL || property == NULL) {
        if (component != NULL) {
            icalcomponent_free(component);
        }
        if (property != NULL) {
            icalproperty_free(property);
        }
        return 0;
    }

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalcomponent_remove_property(component, property);

    // Clean up
    icalcomponent_free(component);
    // Note: The property is already removed and freed by icalcomponent_remove_property

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

    LLVMFuzzerTestOneInput_428(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
