#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!parent_component) {
        return 0;
    }

    // Add a subcomponent to the parent component
    icalcomponent *sub_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!sub_component) {
        icalcomponent_free(parent_component);
        return 0;
    }
    icalcomponent_add_component(parent_component, sub_component);

    // Use the first byte of data to determine the icalcomponent_kind
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0] % ICAL_NO_COMPONENT);

    // Call the function-under-test
    icalcomponent *result = icalcomponent_get_first_component(parent_component, kind);

    // Clean up
    icalcomponent_free(parent_component);

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

    LLVMFuzzerTestOneInput_31(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
