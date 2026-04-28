#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for safe string operations
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Clean up the allocated memory for ical_data
    free(ical_data);

    // If parsing is successful, perform operations on the component
    if (component != NULL) {
        // Example operation: retrieve the first event component
        icalcomponent *event = icalcomponent_get_first_component(component, ICAL_VEVENT_COMPONENT);
        if (event != NULL) {
            // Perform operations on the event, e.g., get the summary
            icalproperty *summary = icalcomponent_get_first_property(event, ICAL_SUMMARY_PROPERTY);
            if (summary != NULL) {
                const char *summary_text = icalproperty_get_summary(summary);
                // Use the summary_text in some way, e.g., log it or manipulate it
            }
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

    LLVMFuzzerTestOneInput_137(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
