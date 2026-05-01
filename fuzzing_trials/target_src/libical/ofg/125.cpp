extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h> // Include string.h for memcpy
    #include <stdlib.h> // Include stdlib.h for malloc and free
}

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Create a buffer to store the input data as a string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *parsedComponent = icalparser_parse_string(inputData);

    // If parsing was successful, use the parsed component
    if (parsedComponent != NULL) {
        icalcomponent *innerComponent = icalcomponent_get_first_component(parsedComponent, ICAL_ANY_COMPONENT);
        if (innerComponent != NULL) {
            // Call the function-under-test
            icalproperty *property = icalcomponent_get_current_property(innerComponent);
            // Optionally, do something with the property
            (void)property; // Suppress unused variable warning
        }
        icalcomponent_free(parsedComponent);
    }

    // Clean up
    free(inputData);
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_125(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
