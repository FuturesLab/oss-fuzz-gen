#include <libical/ical.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = nullptr;
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT; // Use a valid icalcomponent_kind

    // Create a dummy icalcomponent for fuzzing
    component = icalcomponent_new(kind);
    if (component == nullptr) {
        return 0; // Exit if component creation fails
    }

    // Call the function-under-test
    icalcomponent *next_component = icalcomponent_get_next_component(component, kind);

    // Clean up
    if (component != nullptr) {
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_168(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
