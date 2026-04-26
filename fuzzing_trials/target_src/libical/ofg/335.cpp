#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_335(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = nullptr;
    
    // Ensure the size is sufficient for creating a valid icalcomponent
    if (size > 0) {
        // Create a temporary string from the input data
        char *input = (char *)malloc(size + 1);
        if (input == nullptr) {
            return 0;
        }
        memcpy(input, data, size);
        input[size] = '\0'; // Null-terminate the string

        // Parse the input string to create an icalcomponent
        component = icalparser_parse_string(input);
        free(input);
    }

    // Call the function-under-test if the component is not NULL
    if (component != nullptr) {
        char *name = icalcomponent_get_component_name_r(component);
        // Use the name in some way to avoid compiler optimizations removing the call
        if (name != nullptr) {
            // For example, print it or log it
            // printf("Component Name: %s\n", name);
        }

        // Free the component
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

    LLVMFuzzerTestOneInput_335(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
