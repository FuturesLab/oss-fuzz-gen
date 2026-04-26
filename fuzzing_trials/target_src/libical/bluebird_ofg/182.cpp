#include <string.h>
#include <sys/stat.h>
#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0; // Ensure there's enough data for two icaltimetype structures
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0; // If component creation fails, return
    }

    // Create two icaltimetype structures from the input data
    struct icaltimetype time1 = *((struct icaltimetype *)data);
    struct icaltimetype time2 = *((struct icaltimetype *)(data + sizeof(struct icaltimetype)));

    // Call the function-under-test
    bool result = icalproperty_recurrence_is_excluded(component, &time1, &time2);

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

    LLVMFuzzerTestOneInput_182(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
