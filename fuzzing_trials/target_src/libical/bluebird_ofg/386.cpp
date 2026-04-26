#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_386(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating an icalcomponent and icalproperty
    if (size < 2) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the icalcomponent_kind
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0] % (ICAL_NO_COMPONENT + 1));

    // Use the second byte of data to create a summary string
    char summary[2] = { static_cast<char>(data[1]), '\0' };

    // Create a dummy icalproperty to add to the component
    icalproperty *property = icalproperty_new_summary(summary);
    if (property == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalcompiter iter = icalcomponent_end_component(component, kind);

    // Iterate over the component using the iterator to ensure coverage
    while (icalcompiter_is_valid(&iter)) {
        icalcomponent *current = icalcompiter_deref(&iter);
        if (current != NULL) {
            // Perform some operations on the current component
            icalcomponent_kind current_kind = icalcomponent_isa(current);
            (void)current_kind; // Suppress unused variable warning
        }
        icalcompiter_next(&iter);
    }

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

    LLVMFuzzerTestOneInput_386(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
