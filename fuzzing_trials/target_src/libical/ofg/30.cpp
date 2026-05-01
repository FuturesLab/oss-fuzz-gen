#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure the data has at least one byte for a null-terminated string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *description = (char *)malloc(size + 1);
    if (description == NULL) return 0;
    memcpy(description, data, size);
    description[size] = '\0';

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(description);
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_description(component, description);

    // Serialize the component to a string
    char *component_str = icalcomponent_as_ical_string(component);
    if (component_str != NULL) {
        // Parse the component string back to a new component
        icalcomponent *parsed_component = icalparser_parse_string(component_str);
        if (parsed_component != NULL) {
            // Further operations can be done on parsed_component if needed
            icalcomponent_free(parsed_component);
        }
    }

    // Clean up
    icalcomponent_free(component);
    free(description);

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

    LLVMFuzzerTestOneInput_30(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
