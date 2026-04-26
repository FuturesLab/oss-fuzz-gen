#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <libical/ical.h>

extern "C" {
    #include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput_1181(const uint8_t *data, size_t size) {
    // Initialize libical component
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Ensure data is non-empty and of a reasonable size for parsing
    if (size > 0 && size < 1024) {
        // Create a temporary buffer to hold the data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data == NULL) {
            icalcomponent_free(component);
            return 0;
        }

        // Copy data to the temporary buffer and null-terminate it
        memcpy(temp_data, data, size);
        temp_data[size] = '\0';

        // Parse the data into the component
        icalcomponent *parsed_component = icalparser_parse_string(temp_data);
        if (parsed_component != NULL) {
            // Call the function-under-test
            const char *component_name = icalcomponent_get_component_name(parsed_component);

            // Use the component name in some way to avoid compiler optimizations removing the call
            if (component_name != NULL) {
                // For example, just print it (in a real fuzzer, you might log this)
                printf("Component Name: %s\n", component_name);
            }

            // Free the parsed component
            icalcomponent_free(parsed_component);
        }

        // Free the temporary buffer
        free(temp_data);
    }

    // Free the original component
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

    LLVMFuzzerTestOneInput_1181(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
