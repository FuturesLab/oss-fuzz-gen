#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    // All libical headers and functions should be wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1104(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RESOURCES_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Convert data to a string and set it as the value of the property
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0'; // Null-terminate the string

    icalproperty_set_value(prop, icalvalue_new_text(value));

    // Call the function under test
    const char *resources = icalproperty_get_resources(prop);

    // Clean up
    free(value);
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

    LLVMFuzzerTestOneInput_1104(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
