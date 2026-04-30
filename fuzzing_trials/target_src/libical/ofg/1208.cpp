#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_1208(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent structure
    icalcomponent *root = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *event = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_component(root, event);

    // Ensure there is at least one component to retrieve
    icalcomponent *subcomponent = icalcomponent_new(ICAL_VTODO_COMPONENT);
    icalcomponent_add_component(event, subcomponent);

    // Define the kind of component to retrieve
    icalcomponent_kind kind = ICAL_VTODO_COMPONENT;

    // Call the function-under-test
    icalcomponent *next_component = icalcomponent_get_next_component(event, kind);

    // Clean up
    icalcomponent_free(root);

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

    LLVMFuzzerTestOneInput_1208(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
