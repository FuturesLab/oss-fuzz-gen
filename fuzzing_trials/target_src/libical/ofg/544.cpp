#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_544(const uint8_t *data, size_t size) {
    // Ensure the data is not empty before using it
    if (size == 0) {
        return 0;
    }

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Use a portion of the data as a string for the property name
    char *property_name = (char *)malloc(size + 1);
    if (!property_name) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(property_name, data, size);
    property_name[size] = '\0'; // Null-terminate the string

    // Set the property name using the fuzzed data
    icalproperty_set_name(prop, property_name);

    // Convert the first byte of data to an integer for max component size
    int max_component_size = static_cast<int>(data[0]);

    // Call the function-under-test
    icalproperty_set_maxcomponentsize(prop, max_component_size);

    // Clean up
    free(property_name);
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

    LLVMFuzzerTestOneInput_544(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
