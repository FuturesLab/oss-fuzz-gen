#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) return 0;

    // Create a temporary buffer to store the parameter name
    char *param_name = (char *)malloc(size + 1);
    if (param_name == NULL) return 0; // Ensure memory allocation was successful

    // Copy data into param_name and null-terminate it
    memcpy(param_name, data, size);
    param_name[size] = '\0';

    // Create a dummy icalproperty object for testing
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        free(param_name);
        return 0;
    }

    // Add a parameter to the property to ensure there is something to remove
    icalparameter *param = icalparameter_new_from_string(param_name);
    if (param != NULL) {
        icalproperty_add_parameter(property, param);
    }

    // Call the function-under-test
    icalproperty_remove_parameter_by_name(property, param_name);

    // Clean up
    icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_219(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
