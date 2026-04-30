#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_641(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a meaningful null-terminated string
    if (size < 2) { // Adjusted to ensure at least one character and null-terminator
        return 0;
    }

    // Create a null-terminated string from the input data
    char *param = (char *)malloc(size + 1);
    if (param == NULL) {
        return 0;
    }
    memcpy(param, data, size);
    param[size] = '\0';

    // Create a dummy icalproperty object with a specific property type
    icalproperty *property = icalproperty_new(ICAL_X_PROPERTY);
    if (property == NULL) {
        free(param);
        return 0;
    }

    // Set a valid patch parameter to ensure the function is called with meaningful data
    icalproperty_set_patchparameter(property, param);

    // Retrieve the parameter to ensure the function has been invoked correctly
    const char* retrieved_param = icalproperty_get_patchparameter(property);
    if (retrieved_param != NULL) {
        // Check if the retrieved parameter matches the input
        if (strcmp(retrieved_param, param) != 0) {
            // Log an error or handle the mismatch case
        }
    }

    // Additional operations to increase code coverage
    // Attempt to clone the property and check if the clone is successful
    icalproperty *cloned_property = icalproperty_clone(property);
    if (cloned_property != NULL) {
        // Check if the cloned property has the same parameter
        const char* cloned_param = icalproperty_get_patchparameter(cloned_property);
        if (cloned_param != NULL && strcmp(cloned_param, param) == 0) {
            // Optionally, log or handle successful clone verification
        }
        icalproperty_free(cloned_property);
    }

    // Attempt to convert the property to a string and back to increase coverage
    const char *property_str = icalproperty_as_ical_string(property);
    if (property_str != NULL) {
        icalproperty *parsed_property = icalproperty_new_from_string(property_str);
        if (parsed_property != NULL) {
            icalproperty_free(parsed_property);
        }
        // No need to free property_str as it is managed by libical
    }

    // Clean up
    icalproperty_free(property);
    free(param);

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

    LLVMFuzzerTestOneInput_641(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
