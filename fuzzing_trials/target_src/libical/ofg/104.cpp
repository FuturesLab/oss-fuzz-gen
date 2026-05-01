#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be meaningful
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(inputData);

    // Perform operations on 'component' if it is successfully created
    if (component != NULL) {
        // Example operation: convert component to string and print
        char *componentStr = icalcomponent_as_ical_string(component);
        if (componentStr != NULL) {
            // Normally, you would do something with 'componentStr'
            // For example, logging it or using it in further processing
        }

        // Free the component
        icalcomponent_free(component);
    }

    // Free the input data
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

    LLVMFuzzerTestOneInput_104(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
