#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_391(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < sizeof(icalproperty_status)) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract an icalproperty_status value from the input data
    icalproperty_status status = static_cast<icalproperty_status>(data[0]);

    // Call the function-under-test
    icalcomponent_set_status(component, status);

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

    LLVMFuzzerTestOneInput_391(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
