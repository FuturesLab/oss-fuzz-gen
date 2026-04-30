#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h> // Ensure libical C headers are included within extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Initialize a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the data is not empty
    if (size > 0) {
        // Create a string from the input data
        char *ical_string = (char *)malloc(size + 1);
        if (ical_string == NULL) {
            return 0; // Memory allocation failed
        }
        memcpy(ical_string, data, size);
        ical_string[size] = '\0';

        // Parse the string into the icalcomponent
        icalcomponent *parsed_component = icalparser_parse_string(ical_string);
        if (parsed_component != NULL) {
            icalcomponent_add_component(component, parsed_component);
        }

        free(ical_string);
    }

    // Call the function-under-test
    icalproperty_method method = icalcomponent_get_method(component);

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

    LLVMFuzzerTestOneInput_12(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
