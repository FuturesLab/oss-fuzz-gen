#include <stdint.h>

// Wrap necessary includes and declarations with extern "C"
extern "C" {
    #include <libical/ical.h> // Correct header for libical functions
}

extern "C" int LLVMFuzzerTestOneInput_419(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract meaningful data
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract icalproperty_kind from the data
    icalproperty_kind prop_kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Call the function-under-test
    icalproperty *property = icalcomponent_get_first_property(component, prop_kind);

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

    LLVMFuzzerTestOneInput_419(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
