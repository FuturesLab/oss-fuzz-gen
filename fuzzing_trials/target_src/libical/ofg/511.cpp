#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_511(const uint8_t *data, size_t size) {
    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure the data size is valid for setting a property value
    if (size > 0) {
        // Create a string from the input data
        char *value = (char *)malloc(size + 1);
        if (value != NULL) {
            memcpy(value, data, size);
            value[size] = '\0';  // Null-terminate the string

            // Set the value to the icalproperty
            icalproperty_set_value(prop, icalvalue_new_string(value));

            // Free the allocated string
            free(value);

            // Call the function-under-test
            const char *name = icalproperty_get_name(prop);

            // Use the result to prevent compiler optimizations
            if (name != NULL) {
                // Output the result
                printf("Property name: %s\n", name);
            }
        }
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_511(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
