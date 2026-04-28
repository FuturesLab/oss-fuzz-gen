#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalparser.h>
}

extern "C" int LLVMFuzzerTestOneInput_1232(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent from the input data
    icalcomponent *component = nullptr;
    
    // Ensure size is non-zero to avoid passing null data
    if (size > 0) {
        // Convert input data to a string for icalparser_parse_string
        char *ical_data = (char *)malloc(size + 1);
        if (ical_data == nullptr) {
            return 0;  // Memory allocation failed
        }
        memcpy(ical_data, data, size);
        ical_data[size] = '\0';  // Null-terminate the string

        // Parse the string into an icalcomponent
        component = icalparser_parse_string(ical_data);

        // Free the allocated string
        free(ical_data);
    }

    // Check restrictions if the component is successfully created
    if (component != nullptr) {
        bool result = icalcomponent_check_restrictions(component);

        // Clean up the component after use
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

    LLVMFuzzerTestOneInput_1232(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
