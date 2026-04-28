#include <string.h>
#include <sys/stat.h>
extern "C" {
#include "libical/ical.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *param_name = static_cast<char *>(malloc(size + 1));
    if (!param_name) {
        return 0;
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0';

    // Create a dummy icalproperty object with a specific property type
    icalproperty *prop = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (!prop) {
        free(param_name);
        return 0;
    }

    // Set a sample parameter to the property to ensure the function under test has something to work with
    icalproperty_add_parameter(prop, icalparameter_new_x(param_name));

    // Call the function under test
    char *result = icalproperty_get_parameter_as_string_r(prop, param_name);

    // Clean up
    if (result) {
        icalmemory_free_buffer(result);
    }
    icalproperty_free(prop);
    free(param_name);

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

    LLVMFuzzerTestOneInput_28(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
