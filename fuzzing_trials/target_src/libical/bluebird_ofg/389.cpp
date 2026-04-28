#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_389(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Split the input data into two strings
    size_t mid = size / 2;
    char *param_name = (char *)malloc(mid + 1);
    char *param_value = (char *)malloc(size - mid + 1);

    if (param_name == NULL || param_value == NULL) {
        // Clean up and return if memory allocation fails
        if (param_name != NULL) free(param_name);
        if (param_value != NULL) free(param_value);
        icalproperty_free(prop);
        return 0;
    }

    memcpy(param_name, data, mid);
    param_name[mid] = '\0';

    memcpy(param_value, data + mid, size - mid);
    param_value[size - mid] = '\0';

    // Call the function-under-test
    icalproperty_set_parameter_from_string(prop, param_name, param_value);

    // Clean up
    free(param_name);
    free(param_value);
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

    LLVMFuzzerTestOneInput_389(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
