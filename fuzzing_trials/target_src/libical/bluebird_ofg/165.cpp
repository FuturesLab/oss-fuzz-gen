#include <string.h>
#include <sys/stat.h>
#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) return 0;

    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!component) return 0;

    // Use the first byte of data to determine the icalproperty_kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Add a property of the determined kind to the component
    icalproperty *property = icalproperty_new(kind);
    if (property) {
        icalcomponent_add_property(component, property);
    }

    // Call the function-under-test
    icalcomponent_remove_property_by_kind(component, kind);

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

    LLVMFuzzerTestOneInput_165(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
