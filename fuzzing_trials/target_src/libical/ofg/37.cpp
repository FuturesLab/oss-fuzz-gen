#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Initialize the iCalendar component
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Create a string from the fuzzing data
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the iCalendar data into the component
    icalcomponent *parsed_component = icalparser_parse_string(ical_str);
    if (parsed_component != NULL) {
        // Call the function-under-test
        int sequence = icalcomponent_get_sequence(parsed_component);

        // Optionally, use the sequence number for further logic
        (void)sequence; // Suppress unused variable warning

        // Free the parsed component
        icalcomponent_free(parsed_component);
    }

    // Free allocated resources
    free(ical_str);
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

    LLVMFuzzerTestOneInput_37(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
