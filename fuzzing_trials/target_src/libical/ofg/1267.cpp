#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for libical headers

    // Function signature provided for fuzzing
    void icalproperty_normalize(icalproperty *);
}

extern "C" int LLVMFuzzerTestOneInput_1267(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icalproperty
    if (size == 0) {
        return 0;
    }

    // Create an icalproperty from the input data
    // For simplicity, let's assume the data represents a string for property name
    char *property_name = (char *)malloc(size + 1);
    if (property_name == NULL) {
        return 0;
    }

    // Copy data into property_name and null-terminate it
    memcpy(property_name, data, size);
    property_name[size] = '\0';

    // Create an icalproperty using the property name
    icalproperty *prop = icalproperty_new_from_string(property_name);

    // Free the allocated property_name as it is no longer needed
    free(property_name);

    // Check if the property was successfully created
    if (prop != NULL) {
        // Call the function-under-test
        icalproperty_normalize(prop);

        // Free the icalproperty after use
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_1267(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
