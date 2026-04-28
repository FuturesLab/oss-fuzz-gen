#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1033(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary string to hold the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Memory allocation failed, exit
    }

    // Copy the data into the inputData buffer and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Free the input data buffer
    free(inputData);

    if (component != NULL) {
        // Call the function-under-test
        icalcomponent *firstRealComponent = icalcomponent_get_first_real_component(component);

        // Perform any additional operations or checks if necessary

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1033(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
