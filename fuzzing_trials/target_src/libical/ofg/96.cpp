#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent and icalproperty
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_comment("Sample comment");

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Initialize the icalproperty iterator
    icalproperty *result = NULL;
    for (icalproperty *prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
         prop != NULL;
         prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {
        result = prop;
    }

    // Clean up
    if (result != NULL) {
        icalproperty_free(result);
    }
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

    LLVMFuzzerTestOneInput_96(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
