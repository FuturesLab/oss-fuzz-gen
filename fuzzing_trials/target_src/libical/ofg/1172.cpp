#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1172(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a meaningful icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a new icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Set some data to the icalproperty using the input data
    // Here we assume that the input data is a valid string for simplicity
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    icalproperty_set_value(property, icalvalue_new_string(value));

    // Call the function-under-test
    icalproperty_method method = icalproperty_get_method(property);

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

    LLVMFuzzerTestOneInput_1172(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
