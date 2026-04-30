#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <libical/ical.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data as a string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }

    // Copy the input data and null-terminate the string
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Free the temporary input data buffer
    free(inputData);

    // If parsing was successful, call the function-under-test
    if (component != NULL) {
        char *icalString = icalcomponent_as_ical_string(component);

        // Normally, you would do something with icalString here
        // For fuzzing, we just ensure it was generated

        // Free the generated string
        if (icalString != NULL) {
            free(icalString);
        }

        // Free the icalcomponent
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_32(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
