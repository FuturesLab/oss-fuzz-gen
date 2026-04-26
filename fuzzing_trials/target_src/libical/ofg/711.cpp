#include <stdint.h>
#include <stdlib.h>
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the ical library
}

extern "C" int LLVMFuzzerTestOneInput_711(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a property
    if (size < 1) {
        return 0;
    }

    // Create a new icalproperty
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Set a value to the property using the fuzz data
    // Here we assume the data is a string; adjust as necessary for other types
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    icalvalue *ical_val = icalvalue_new_from_string(ICAL_ANY_VALUE, value);
    if (ical_val != NULL) {
        icalproperty_set_value(property, ical_val);
    }

    // Call the function under test
    icalproperty_querylevel result = icalproperty_get_querylevel(property);

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

    LLVMFuzzerTestOneInput_711(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
