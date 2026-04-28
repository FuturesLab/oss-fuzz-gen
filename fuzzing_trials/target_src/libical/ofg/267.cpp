#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h> // Assuming the correct path to the libical headers

extern "C" {
    // Include necessary C headers and function declarations
    void icalproperty_set_proximity(icalproperty *prop, icalproperty_proximity proximity);
}

extern "C" int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 2) {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_PROXIMITY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the proximity value
    icalproperty_proximity proximity = static_cast<icalproperty_proximity>(data[0] % (ICAL_PROXIMITY_NONE + 1));

    // Call the function-under-test
    icalproperty_set_proximity(property, proximity);

    // Additional logic to increase code coverage
    // Use more of the input data to perform further operations
    if (size > 2) {
        // For example, manipulate the property further based on additional data
        int some_other_value = data[1] % (ICAL_PROXIMITY_NONE + 1);
        // Hypothetical function to further manipulate the property
        // icalproperty_set_some_other_value(property, some_other_value);
    }

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_267(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
