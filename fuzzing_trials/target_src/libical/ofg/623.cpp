#include <libical/ical.h>
#include <cstddef>
#include <cstdint>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_623(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent and icalproperty for testing
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_summary("Test Summary");
    icalcomponent_add_property(component, property);

    // Initialize an icalproperty to iterate over properties
    icalproperty *iter_property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

    // Call the function-under-test
    icalproperty *result = iter_property;

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

    LLVMFuzzerTestOneInput_623(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
