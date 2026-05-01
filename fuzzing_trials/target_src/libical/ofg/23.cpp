#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Initialize a non-null icalproperty object using data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);
    icalproperty *property = icalproperty_new(kind);

    // Ensure the property is not NULL
    if (property == NULL) {
        return 0;
    }

    // Create a dummy icalcomponent and attach the property to it
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        icalproperty_free(property);
        return 0;
    }
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalcomponent *parent = icalproperty_get_parent(property);

    // Perform some operations with the parent if needed
    if (parent != NULL) {
        // Example operation: Get the first property of the parent component
        icalproperty *first_property = icalcomponent_get_first_property(parent, ICAL_ANY_PROPERTY);
        // Do something with first_property if needed
    }

    // Clean up
    icalcomponent_free(component); // This will also free the property

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

    LLVMFuzzerTestOneInput_23(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
