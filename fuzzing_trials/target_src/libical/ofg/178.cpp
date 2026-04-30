#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype dtstart;
    memcpy(&dtstart, data, sizeof(struct icaltimetype));

    // Validate the icaltimetype to ensure it's a valid date-time
    if (dtstart.year < 1 || dtstart.year > 9999 ||
        dtstart.month < 1 || dtstart.month > 12 ||
        dtstart.day < 1 || dtstart.day > 31) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_dtstart(component, dtstart);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_178(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
