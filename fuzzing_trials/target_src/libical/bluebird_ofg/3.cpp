#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    icalcomponent *component = NULL;
    icalcomponent *parent = NULL;
    icalcomponent *child = NULL;
    icalproperty *property = NULL;

    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize an icalcomponent from the input data if possible
    if (size > 0) {
        component = icalcomponent_new_from_string(null_terminated_data);
    }

    // If the component is NULL, create a default one for fuzzing
    if (component == NULL) {
        component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
        parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
        child = icalcomponent_new(ICAL_VTODO_COMPONENT);
        property = icalproperty_new_summary("Sample Summary");

        icalcomponent_add_component(parent, component);
        icalcomponent_add_component(component, child);
        icalcomponent_add_property(component, property);
    }

    // Call the function-under-test
    bool result = icalcomponent_check_restrictions(component);

    // Clean up
    // Correct the order of freeing components to avoid use-after-free
    if (child != NULL) {
        icalcomponent_remove_component(component, child);
        icalcomponent_free(child);
    }
    if (property != NULL) {
        icalcomponent_remove_property(component, property);
        icalproperty_free(property);
    }
    if (component != NULL) {
        icalcomponent_remove_component(parent, component);
        icalcomponent_free(component);
    }
    if (parent != NULL) {
        icalcomponent_free(parent);
    }

    // Free the allocated memory for null-terminated data
    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
