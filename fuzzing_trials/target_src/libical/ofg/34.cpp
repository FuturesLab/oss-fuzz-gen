#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *root_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *sub_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    
    // Add a property to the sub-component
    icalproperty *prop = icalproperty_new_summary("Sample Event");
    icalcomponent_add_property(sub_component, prop);

    // Add the sub-component to the root component
    icalcomponent_add_component(root_component, sub_component);

    // Call the function-under-test
    icalcomponent *current_component = icalcomponent_get_current_component(root_component);

    // Clean up
    icalcomponent_free(root_component);

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

    LLVMFuzzerTestOneInput_34(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
