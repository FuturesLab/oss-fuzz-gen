#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Initialize variables
    icalproperty *property = nullptr;
    icalcomponent *component = nullptr;

    // Create a dummy icalproperty
    property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == nullptr) {
        return 0; // Exit if property creation failed
    }

    // Create a dummy icalcomponent
    component = icalcomponent_new(ICAL_NO_COMPONENT);
    if (component == nullptr) {
        icalproperty_free(property);
        return 0; // Exit if component creation failed
    }

    // Call the function-under-test
    icalproperty_set_parent(property, component);

    // Clean up
    icalcomponent_free(component);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_187(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
