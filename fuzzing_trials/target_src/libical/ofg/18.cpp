#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Check if the input data is large enough to be used meaningfully
    if (size == 0) {
        return 0; // No operation if there's no data
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Parse the input data as an iCal component
    icalcomponent *component = icalparser_parse_string(inputData);

    // Check if the component was created successfully
    if (component != NULL) {
        // Perform operations on the component if needed
        // For example, convert to string or add properties

        // Free the component after use
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_18(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
