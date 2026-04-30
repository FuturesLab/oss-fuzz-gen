#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include the cstring header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1303(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract an icaltimetype from the input data
    struct icaltimetype dtstart;
    memcpy(&dtstart, data, sizeof(struct icaltimetype));

    // Ensure the icaltimetype is valid
    if (dtstart.year < 1 || dtstart.year > 9999 || 
        dtstart.month < 1 || dtstart.month > 12 || 
        dtstart.day < 1 || dtstart.day > 31) {
        icalcomponent_free(component);
        return 0;
    }

    // Call the function under test
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1303(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
