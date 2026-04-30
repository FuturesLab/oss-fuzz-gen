#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

// Define a compatible line generator function
extern "C" char* line_gen_func_1351(char *s, unsigned long size, void *d) {
    // For testing purposes, return the input string itself
    return s;
}

extern "C" int LLVMFuzzerTestOneInput_1351(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Initialize an icalparser
    icalparser *parser = icalparser_new();
    if (parser == nullptr) {
        free(inputData);
        return 0;
    }

    // Parse the input data to create an icalcomponent
    icalparser_set_gen_data(parser, inputData);
    icalcomponent *component = icalparser_parse(parser, line_gen_func_1351);
    if (component != nullptr) {
        icalproperty *property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
        while (property != nullptr) {
            // Call the function-under-test
            const char *patchVersion = icalproperty_get_patchversion(property);
            // Do something with patchVersion if needed
            property = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY);
        }
        icalcomponent_free(component);
    }

    // Cleanup
    icalparser_free(parser);
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

    LLVMFuzzerTestOneInput_1351(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
