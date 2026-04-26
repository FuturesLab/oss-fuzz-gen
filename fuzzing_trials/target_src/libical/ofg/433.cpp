#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the missing header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_433(const uint8_t *data, size_t size) {
    // Check if the input data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        return 0; // Memory allocation failed
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_data);

    // If parsing was successful, call the function-under-test
    if (component != NULL) {
        icalcomponent_kind kind = icalcomponent_isa(component);
        // Perform additional operations if needed
        icalcomponent_free(component);
    }

    // Clean up
    free(input_data);

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

    LLVMFuzzerTestOneInput_433(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
