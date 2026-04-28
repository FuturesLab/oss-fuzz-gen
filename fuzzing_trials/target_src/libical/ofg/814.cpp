#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_814(const uint8_t *data, size_t size) {
    // Initialize the variables
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT; // Use a valid kind as a starting point

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcompiter iter = icalcomponent_begin_component(component, kind);

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

    LLVMFuzzerTestOneInput_814(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
