#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_438(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a valid string
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = new char[size + 1];
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Ensure the component is not NULL
    if (!component) {
        delete[] inputData;
        return 0;
    }

    // Initialize the iterator with the component
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function-under-test
    icalcomponent *result = icalcompiter_deref(&iter);

    // Optionally perform some operations on the result to increase coverage
    if (result) {
        icalcomponent_get_first_property(result, ICAL_ANY_PROPERTY);
    }

    // Clean up
    icalcomponent_free(component);
    delete[] inputData;

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

    LLVMFuzzerTestOneInput_438(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
