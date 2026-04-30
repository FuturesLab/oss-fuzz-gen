#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1087(const uint8_t *data, size_t size) {
    // Initialize the variables
    icalcomponent *parent = nullptr;
    icalcomponent *child = nullptr;

    // Create a dummy parent component
    parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Create a dummy child component
    child = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Add the child to the parent
    icalcomponent_add_component(parent, child);

    // Fuzzing: Call the function under test
    icalcomponent_remove_component(parent, child);

    // Clean up
    icalcomponent_free(parent);

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

    LLVMFuzzerTestOneInput_1087(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
