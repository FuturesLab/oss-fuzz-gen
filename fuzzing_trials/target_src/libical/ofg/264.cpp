#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create an icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Convert input data to a string
    char *str_data = (char *)malloc(size + 1);
    if (str_data == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(str_data, data, size);
    str_data[size] = '\0';

    // Parse the string data into an icalcomponent
    icalcomponent *parsed_component = icalparser_parse_string(str_data);
    free(str_data);

    if (parsed_component != NULL) {
        // Create an icalcompiter from the parsed component
        icalcompiter iter = icalcomponent_begin_component(parsed_component, ICAL_ANY_COMPONENT);

        // Call the function-under-test
        bool is_valid = icalcompiter_is_valid(&iter);

        // Cleanup
        icalcomponent_free(parsed_component);
    }

    // Cleanup
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

    LLVMFuzzerTestOneInput_264(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
