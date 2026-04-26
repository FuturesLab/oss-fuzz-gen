#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for size_t

extern "C" {
    #include "libical/ical.h"
    // Removed the include for "libical/icalderived.h" as it does not exist
    #include "libical/icalproperty.h" // Include for icalproperty functions
    // Removed the include for "libical/icalpvl.h" as it does not exist
}

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent with some dummy data
    icalcomponent *comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    
    // Ensure the component is not empty by adding a dummy property
    icalproperty *prop = icalproperty_new_comment("Dummy comment");
    icalcomponent_add_property(comp, prop);

    // Call the function-under-test
    icalproperty *retrieved_prop = icalcomponent_get_first_property(comp, ICAL_COMMENT_PROPERTY);

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

    LLVMFuzzerTestOneInput_139(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
