#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1026(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = nullptr;
    if (size > 0) {
        // Create a string from the input data
        char *ical_str = static_cast<char *>(malloc(size + 1));
        if (ical_str == nullptr) {
            return 0;
        }
        memcpy(ical_str, data, size);
        ical_str[size] = '\0';

        // Parse the string into an icalcomponent
        component = icalparser_parse_string(ical_str);
        free(ical_str);
    }

    // If the component is successfully created, proceed with fuzzing
    if (component != nullptr) {
        // Define a valid icalcomponent_kind. For fuzzing, we can try different kinds.
        icalcomponent_kind kinds[] = {
            ICAL_VEVENT_COMPONENT,
            ICAL_VTODO_COMPONENT,
            ICAL_VJOURNAL_COMPONENT,
            ICAL_VFREEBUSY_COMPONENT,
            ICAL_VTIMEZONE_COMPONENT,
            ICAL_XSTANDARD_COMPONENT,
            ICAL_XDAYLIGHT_COMPONENT,
            ICAL_VALARM_COMPONENT
        };

        // Iterate over different kinds and call the function-under-test
        for (auto kind : kinds) {
            int count = icalcomponent_count_components(component, kind);
            (void)count; // Use the result to prevent compiler warnings
        }

        // Free the component after use
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1026(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
