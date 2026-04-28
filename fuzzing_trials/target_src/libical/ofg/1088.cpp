#include <cstddef>
#include <cstdint>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1088(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Add the child component to the parent
    icalcomponent_add_component(parent, child);

    // Fuzzing: Remove the child component from the parent
    icalcomponent_remove_component(parent, child);

    // Clean up
    icalcomponent_free(parent);
    // The child is already removed, so it's not necessary to free it separately

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

    LLVMFuzzerTestOneInput_1088(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
