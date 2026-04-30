#include <sys/stat.h>
#include <string.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to extract meaningful information
    if (size < 1) {
        return 0;
    }

    // Convert input data to a null-terminated string
    char *ical_data = (char *)malloc(size + 1);
    if (!ical_data) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);
    free(ical_data);

    if (component == NULL) {
        return 0;
    }

    // Iterate over all properties in the component
    for (icalproperty *prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
         prop != NULL;
         prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {
        // Process each property
        icalproperty_kind kind = icalproperty_isa(prop);
        // Call the function-under-test
        icalpropiter propiter = icalcomponent_begin_property(component, kind);
        (void)propiter; // Suppress unused variable warning
    }

    // Clean up the icalcomponent object
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_34(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
