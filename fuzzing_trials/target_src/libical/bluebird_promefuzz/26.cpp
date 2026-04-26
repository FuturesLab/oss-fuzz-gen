#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <cstdint>
#include <cstddef>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure we create VCALENDAR components for merging
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *component_to_merge = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Fuzz icalcomponent_get_current_component
    icalcomponent *current_component = icalcomponent_get_current_component(component);

    // Fuzz icalcomponent_merge_component
    if (component && component_to_merge) {
        icalcomponent_merge_component(component, component_to_merge);
        component_to_merge = nullptr; // No longer valid after merging
    }

    // Fuzz icalcomponent_get_inner
    icalcomponent *inner_component = icalcomponent_get_inner(component);

    // Fuzz icalcomponent_set_parent
    if (inner_component) {
        icalcomponent_set_parent(inner_component, component);
    }

    // Fuzz icalcomponent_clone
    icalcomponent *cloned_component = icalcomponent_clone(component);

    // Cleanup
    if (component) {
        icalcomponent_free(component);
    }
    if (cloned_component) {
        icalcomponent_free(cloned_component);
    }

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

    LLVMFuzzerTestOneInput_26(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
