#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent and icalproperty
    icalcomponent *component = icalcomponent_vanew(
        ICAL_VCALENDAR_COMPONENT,
        icalproperty_new_version("2.0"),
        icalproperty_new_prodid("-//Sample Corp//NONSGML Event//EN"),
        0);

    icalproperty *property = icalproperty_new_summary("Sample Event");

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Fuzzing logic: Attempt to remove the property using the function-under-test
    icalcomponent_remove_property(component, property);

    // Clean up
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

    LLVMFuzzerTestOneInput_55(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
