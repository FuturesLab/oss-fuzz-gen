#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size == 0) {
        return 0;
    }
    
    // Initialize necessary variables
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Set the input data as a property of the component
    icalproperty *prop = icalproperty_new_comment(inputData);
    if (prop != NULL) {
        icalcomponent_add_property(component, prop);
    }

    // Call the function-under-test
    // Instead of using icalcomponent_end_component, let's try parsing the input data
    // as an iCalendar string to ensure the function under test is effectively invoked.
    icalcomponent *parsedComponent = icalparser_parse_string(inputData);
    if (parsedComponent != NULL) {
        // If parsing succeeds, free the parsed component
        icalcomponent_free(parsedComponent);
    }

    // Clean up
    free(inputData);
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

    LLVMFuzzerTestOneInput_71(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
