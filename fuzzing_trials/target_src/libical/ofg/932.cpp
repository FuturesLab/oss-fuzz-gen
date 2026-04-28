#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_932(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent to create an icalproperty
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (comp == NULL) {
        return 0;
    }

    // Add a property to the component to ensure the iterator has something to iterate over
    icalproperty *prop = icalproperty_new_summary("Sample Summary");
    if (prop == NULL) {
        icalcomponent_free(comp);
        return 0;
    }
    icalcomponent_add_property(comp, prop);

    // Initialize an icalproperty iterator
    icalproperty *next_prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);

    // Iterate over properties using the function-under-test
    while (next_prop != NULL) {
        next_prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY);
    }

    // Clean up
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_932(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
