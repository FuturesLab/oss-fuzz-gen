#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a valid input for icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // If memory allocation fails, exit early
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Parse the input string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputString);

    // Normally, you would do something with the component here,
    // such as manipulating it or checking its properties.
    // Since this is a fuzzing harness, we are primarily interested in
    // ensuring that the function can handle any input without crashing.

    // Clean up the created component to avoid memory leaks
    if (component != NULL) {
        icalcomponent_free(component);
    }

    free(inputString); // Free the allocated memory for the input string

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

    LLVMFuzzerTestOneInput_180(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
