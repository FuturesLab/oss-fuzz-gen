#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_338(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;

    // Ensure the data is not empty
    if (size > 0) {
        // Create a temporary string to hold the input data
        char *input = (char *)malloc(size + 1);
        if (input == nullptr) {
            return 0; // Handle memory allocation failure
        }

        // Copy the data into the input string and null-terminate it
        memcpy(input, data, size);
        input[size] = '\0';

        // Parse the input string into an icalcomponent
        component = icalparser_parse_string(input);

        // Free the input string
        free(input);
    }

    // If the component was successfully created, call the function-under-test
    if (component != nullptr) {
        icalproperty_method method = icalcomponent_get_method(component);

        // Optionally, you can use the 'method' variable here for further testing or logging

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

    LLVMFuzzerTestOneInput_338(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
