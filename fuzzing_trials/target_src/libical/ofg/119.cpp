#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Create a dummy icalcomponent to ensure we have a valid non-NULL input
    icalcomponent *original_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Add some properties to the component
    icalproperty *summary = icalproperty_new_summary("Sample Event");
    icalcomponent_add_property(original_component, summary);

    icalproperty *dtstart = icalproperty_new_dtstart(icaltime_from_string("20231010T100000Z"));
    icalcomponent_add_property(original_component, dtstart);

    // Clone the component
    icalcomponent *cloned_component = icalcomponent_clone(original_component);

    // Clean up
    icalcomponent_free(original_component);
    if (cloned_component != NULL) {
        icalcomponent_free(cloned_component);
    }

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

    LLVMFuzzerTestOneInput_119(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
