#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated
    if (size == 0) {
        return 0; // No data to process
    }

    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Memory allocation failed
    }

    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_x(null_terminated_data);

    // Ensure that the function is exercised correctly
    if (prop != NULL) {
        // Perform additional operations on the property to increase coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_X_PROPERTY) {
            // Access some property details
            const char *value = icalproperty_get_x(prop);
            if (value != NULL) {
                // Process the value to simulate usage
                size_t value_length = strlen(value);
                if (value_length > 0) {
                    // Simulate some processing on the value
                    (void)value_length; // Use the value_length to avoid unused variable warning
                }
            }
        }

        // Additional operations to increase coverage
        icalproperty_set_x(prop, "new_value");
        const char *new_value = icalproperty_get_x(prop);
        if (new_value != NULL) {
            size_t new_value_length = strlen(new_value);
            if (new_value_length > 0) {
                // Simulate some processing on the new value
                (void)new_value_length; // Use the new_value_length to avoid unused variable warning
            }
        }

        // Further operations to increase coverage
        icalproperty_set_x(prop, null_terminated_data);
        const char *reset_value = icalproperty_get_x(prop);
        if (reset_value != NULL) {
            size_t reset_value_length = strlen(reset_value);
            if (reset_value_length > 0) {
                // Simulate some processing on the reset value
                (void)reset_value_length; // Use the reset_value_length to avoid unused variable warning
            }
        }

        icalproperty_free(prop);
    }

    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_97(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
