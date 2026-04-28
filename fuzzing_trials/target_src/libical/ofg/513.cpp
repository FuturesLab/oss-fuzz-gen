#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_513(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent and icalproperty_kind
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty_kind kind = ICAL_ANY_PROPERTY;

    // Add a property to the component to ensure it's not empty
    icalproperty *property = icalproperty_new_summary("Sample Summary");
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalproperty *result = icalcomponent_get_first_property(component, kind);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_513(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
