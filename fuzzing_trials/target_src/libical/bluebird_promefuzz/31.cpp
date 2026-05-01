#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

    // Create a dummy icalcomponent using the library's creation function
    icalcomponent *comp = icalcomponent_new(kind);

    if (comp == NULL) {
        return 0;
    }

    // Test icalcomponent_get_component_name_r
    char *component_name_r = icalcomponent_get_component_name_r(comp);
    if (component_name_r != NULL) {
        free(component_name_r);
    }

    // Test icalcomponent_get_location
    const char *location = icalcomponent_get_location(comp);
    if (location != NULL) {
        // Process location if needed
    }

    // Test icalcomponent_get_description
    const char *description = icalcomponent_get_description(comp);
    if (description != NULL) {
        // Process description if needed
    }

    // Test icalcomponent_get_component_name
    const char *component_name = icalcomponent_get_component_name(comp);
    if (component_name != NULL) {
        // Process component_name if needed
    }

    // Test icalcomponent_get_first_component
    icalcomponent *first_component = icalcomponent_get_first_component(comp, kind);
    if (first_component != NULL) {
        // Process first_component if needed
    }

    // Test icalcomponent_get_comment
    const char *comment = icalcomponent_get_comment(comp);
    if (comment != NULL) {
        // Process comment if needed
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_31(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
