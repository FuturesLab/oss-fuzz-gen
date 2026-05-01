#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent and icalcomponent_kind
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

    // Ensure the data is large enough to simulate a valid component
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            return 0;
        }
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Attempt to parse the data as an icalcomponent
        icalcomponent *parsed_component = icalparser_parse_string(buffer);
        if (parsed_component != NULL) {
            // Assign the parsed component to the component variable
            icalcomponent_free(component);
            component = parsed_component;
        }

        free(buffer);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_113(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
