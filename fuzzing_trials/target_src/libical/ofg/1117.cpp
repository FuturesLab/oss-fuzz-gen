#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_1117(const uint8_t *data, size_t size) {
    // Convert the input data to a string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the input string as an iCalendar component
    icalcomponent *parsed_component = icalparser_parse_string(ical_string);

    // Clean up the input string memory
    free(ical_string);

    // Ensure that the parsed component is not NULL
    if (parsed_component == NULL) {
        return 0;
    }

    // Initialize a parent icalcomponent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure that the parent component is not NULL
    if (parent_component == NULL) {
        icalcomponent_free(parsed_component);
        return 0;
    }

    // Add the parsed component to the parent component
    icalcomponent_add_component(parent_component, parsed_component);

    // Clean up
    icalcomponent_free(parent_component);
    // No need to free parsed_component separately as it is now part of parent_component

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

    LLVMFuzzerTestOneInput_1117(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
