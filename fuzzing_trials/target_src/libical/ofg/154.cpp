#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Initialize the iCalendar component
    icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the child component is added to the parent
    icalcomponent_add_component(parent, child);

    // Call the function-under-test with the parent and child components
    icalcomponent_remove_component(parent, child);

    // Clean up
    icalcomponent_free(parent);
    // Note: The child component is freed when the parent is freed

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

    LLVMFuzzerTestOneInput_154(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
