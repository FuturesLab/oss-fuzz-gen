#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_388(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize an icalproperty object with a specific kind
    icalproperty *property = icalproperty_new(ICAL_X_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Initialize an icalparameter object with a specific kind
    icalparameter *parameter = icalparameter_new(ICAL_X_PARAMETER);
    if (parameter == NULL) {
        icalproperty_free(property);
        return 0;
    }

    // Set a value for the parameter using provided data
    char *param_value = static_cast<char *>(malloc(size + 1));
    if (param_value == NULL) {
        icalparameter_free(parameter);
        icalproperty_free(property);
        return 0;
    }
    memcpy(param_value, data, size);
    param_value[size] = '\0';

    icalparameter_set_xname(parameter, param_value);

    // Add the parameter to the property to ensure it's a valid operation
    icalproperty_add_parameter(property, parameter);

    // Call the function-under-test: Modify to ensure it exercises code paths
    // Use icalproperty_get_first_parameter to access the parameter
    icalparameter *retrieved_parameter = icalproperty_get_first_parameter(property, ICAL_X_PARAMETER);
    if (retrieved_parameter != NULL) {
        // Perform operations on the retrieved parameter to ensure coverage
        const char *retrieved_value = icalparameter_get_xname(retrieved_parameter);
        if (retrieved_value != NULL) {
            // Print the retrieved value to ensure it's being used
            // This is just for demonstration; in a real fuzzing setup, you might log or further process this value
            printf("Retrieved parameter value: %s\n", retrieved_value);
        }
    }

    // Clean up
    free(param_value);
    icalproperty_free(property);
    // Note: The parameter is freed when the property is freed

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

    LLVMFuzzerTestOneInput_388(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
