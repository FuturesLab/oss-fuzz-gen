#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

// Wrap the necessary includes and function declarations with extern "C"
extern "C" {
    #include <libical/ical.h>  // Corrected include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize a string buffer with the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Return if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Parse the input string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);

    // Ensure the component is not NULL before calling the function
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_strip_errors(component);

        // Free the icalcomponent after use
        icalcomponent_free(component);
    }

    // Free the allocated input buffer
    free(input);

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

    LLVMFuzzerTestOneInput_116(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
