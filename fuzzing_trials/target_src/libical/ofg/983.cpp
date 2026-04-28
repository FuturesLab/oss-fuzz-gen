#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_983(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before using it as a string
    if (size == 0) {
        return 0; // Exit early if the input size is zero
    }

    // Allocate memory for the input string and ensure it is null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_str);

    // Free the input string buffer after parsing
    free(input_str);

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform operations on the created component
        // For fuzzing purposes, we can convert it to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string (in a real fuzzing environment, this might be logged)
            // Instead of printing, which can cause unnecessary IO operations in fuzzing,
            // we should just ensure the string is valid by checking its length
            size_t component_str_len = strlen(component_str);
            if (component_str_len > 0) {
                // Do something minimal to ensure the string is processed
                volatile char dummy = component_str[0];
                (void)dummy;
            }
            // Free the string after use
            icalmemory_free_buffer(component_str);
        }

        // Free the component after use
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

    LLVMFuzzerTestOneInput_983(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
