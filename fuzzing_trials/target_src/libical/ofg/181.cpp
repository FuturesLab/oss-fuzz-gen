#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    // Ensure all C headers and functions are included within extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;
    
    // Ensure the data is not empty and can be converted to a string
    if (size > 0) {
        // Allocate memory for the component string
        char *componentStr = (char*)malloc(size + 1);
        if (componentStr == nullptr) {
            return 0; // Memory allocation failed
        }
        
        // Copy data to componentStr and null-terminate it
        memcpy(componentStr, data, size);
        componentStr[size] = '\0';

        // Parse the component string
        component = icalparser_parse_string(componentStr);

        // Free the allocated memory for the string
        free(componentStr);
    }

    // If parsing was successful, call the function-under-test
    if (component != nullptr) {
        icalproperty_method method = icalcomponent_get_method(component);

        // Clean up the component
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

    LLVMFuzzerTestOneInput_181(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
