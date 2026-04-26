#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1336(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to split into two strings
    if (size < 2) return 0;

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) return 0;

    // Split the input data into two parts for the parameter name and value
    size_t mid = size / 2;
    char *param_name = (char *)malloc(mid + 1);
    char *param_value = (char *)malloc(size - mid + 1);

    if (param_name == NULL || param_value == NULL) {
        icalproperty_free(prop);
        free(param_name);
        free(param_value);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(param_name, data, mid);
    param_name[mid] = '\0';
    memcpy(param_value, data + mid, size - mid);
    param_value[size - mid] = '\0';

    // Call the function under test
    icalproperty_set_parameter_from_string(prop, param_name, param_value);

    // Clean up
    icalproperty_free(prop);
    free(param_name);
    free(param_value);

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

    LLVMFuzzerTestOneInput_1336(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
