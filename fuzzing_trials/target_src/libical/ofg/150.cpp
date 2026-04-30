#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to proceed
    if (size < 2) {
        return 0;
    }

    // Create two icalcomponent objects
    icalcomponent *component1 = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent *component2 = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure that the components are not NULL
    if (component1 == NULL || component2 == NULL) {
        if (component1 != NULL) {
            icalcomponent_free(component1);
        }
        if (component2 != NULL) {
            icalcomponent_free(component2);
        }
        return 0;
    }

    // Call the function under test
    icalcomponent_set_parent(component1, component2);

    // Clean up
    icalcomponent_free(component1);
    icalcomponent_free(component2);

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

    LLVMFuzzerTestOneInput_150(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
