#include <iostream>
#include <libical/ical.h>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_431(const uint8_t *data, size_t size) {
    // Ensure that the size is non-zero to create a valid string
    if (size == 0) return 0;

    // Create a valid icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) return 0;

    // Allocate memory for the location string and ensure it's null-terminated
    char *location = (char *)malloc(size + 1);
    if (location == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(location, data, size);
    location[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_location(component, location);

    // Clean up
    free(location);
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

    LLVMFuzzerTestOneInput_431(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
