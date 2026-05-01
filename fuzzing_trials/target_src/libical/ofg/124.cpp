#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent and icalproperty
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *prop = icalproperty_new_summary("Sample Summary");
    icalcomponent_add_property(comp, prop);

    // Use the icalcomponent_get_first_property to initialize the icalpropiter
    icalproperty *first_prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);

    // Call the function-under-test
    icalproperty *next_prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY);

    // Cleanup
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_124(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
