#include <cstdint>  // Include for uint8_t
#include <cstdio>   // Include for printf
#include <cstdlib>  // Include for malloc and free
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Ensure that the input data is sufficient to create a valid component
    if (size == 0) {
        return 0; // Exit early if there's no data
    }

    // Create a string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0'; // Null-terminate the string

    // Parse the input string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_str);

    // Free the input string after parsing
    free(input_str);

    // Check if the component is not NULL
    if (component != NULL) {
        // Perform operations on the component if needed
        // For instance, you can convert it to a string or perform other checks
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Optionally print the component string (for debugging purposes)
            // printf("%s\n", component_str);
            // Free the string after use
            icalmemory_free_buffer(component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    } else {
        // Handle the case where the component is NULL
        // This might be due to invalid input data, so we should ensure
        // that the fuzzer is aware of this case by returning a non-zero value
        return 0; // Changed from 1 to 0 to prevent immediate crash
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_41(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
