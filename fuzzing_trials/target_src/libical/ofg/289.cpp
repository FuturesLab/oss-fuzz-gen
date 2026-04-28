#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_289(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for parsing
    char *input = (char *)malloc(size + 1);
    if (!input) return 0;
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);
    free(input);

    if (component == NULL) {
        return 0; // Parsing failed, return early
    }

    // Define an array of possible icalcomponent_kind values to fuzz
    icalcomponent_kind kinds[] = {
        ICAL_ANY_COMPONENT,
        ICAL_VEVENT_COMPONENT,
        ICAL_VTODO_COMPONENT,
        ICAL_VJOURNAL_COMPONENT,
        ICAL_VFREEBUSY_COMPONENT,
        ICAL_VTIMEZONE_COMPONENT,
        ICAL_XSTANDARD_COMPONENT,
        ICAL_XDAYLIGHT_COMPONENT,
        ICAL_VAGENDA_COMPONENT,
        ICAL_VCALENDAR_COMPONENT,
        ICAL_VSCHEDULE_COMPONENT,
        ICAL_VQUERY_COMPONENT,
        ICAL_VCAR_COMPONENT,
        ICAL_X_COMPONENT
    };

    // Iterate through all possible kinds
    for (size_t i = 0; i < sizeof(kinds) / sizeof(kinds[0]); ++i) {
        icalcomponent_kind kind = kinds[i];
        // Call the function under test
        icalcomponent *result = icalcomponent_get_first_component(component, kind);
        (void)result; // Suppress unused variable warning
    }

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

    LLVMFuzzerTestOneInput_289(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
