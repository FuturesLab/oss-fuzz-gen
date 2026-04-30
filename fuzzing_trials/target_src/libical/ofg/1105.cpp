#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1105(const uint8_t *data, size_t size) {
    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RESOURCES_PROPERTY);

    // Ensure the data is not empty and assign it to the icalproperty
    if (size > 0) {
        // Create a string from the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == NULL) {
            icalproperty_free(prop);
            return 0;
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Set the resources property value
        icalproperty_set_resources(prop, inputData);

        // Free the inputData as it's no longer needed
        free(inputData);
    }

    // Call the function-under-test
    const char *resources = icalproperty_get_resources(prop);

    // Use the resources value to prevent compiler optimizations from removing the call
    if (resources) {
        // Do something with resources, e.g., print or log (not required here)
    }

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_1105(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
