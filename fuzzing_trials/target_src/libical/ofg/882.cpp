#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_882(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty object
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ITIPVERSION_PROPERTY);

    // Set a value to the property using the input data
    // Convert the data to a string, ensuring null-termination
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(property);
        return 0;
    }

    memcpy(value, data, size);
    value[size] = '\0';

    // Set the property value
    icalproperty_set_value(property, icalvalue_new_string(value));

    // Call additional functions to increase code coverage
    icalproperty_kind kind = icalproperty_isa(property);
    icalvalue *val = icalproperty_get_value(property);
    if (val != NULL) {
        icalvalue_kind val_kind = icalvalue_isa(val);
        (void)val_kind; // Use the value kind to avoid unused variable warning
    }

    // Clean up
    free(value);
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

    LLVMFuzzerTestOneInput_882(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
