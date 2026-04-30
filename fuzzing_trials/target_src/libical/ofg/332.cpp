#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    // Create a memory context
    icalcomponent *component = NULL;
    icalproperty *property = NULL;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (!inputData) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    component = icalparser_parse_string(inputData);
    if (component != NULL) {
        // Retrieve the first property of the component
        property = icalcomponent_get_first_property(component, ICAL_GEO_PROPERTY);
        if (property != NULL) {
            // Call the function-under-test
            struct icalgeotype geo = icalproperty_get_geo(property);
        }
        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated memory
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_332(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
