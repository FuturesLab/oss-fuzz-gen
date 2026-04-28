#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_801(const uint8_t *data, size_t size) {
    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_POLLPROPERTIES_PROPERTY);

    // Set a non-NULL value if possible
    if (size > 0) {
        // Create a string from the input data
        char *value = (char *)malloc(size + 1);
        if (value == NULL) {
            icalproperty_free(prop);
            return 0;
        }
        memcpy(value, data, size);
        value[size] = '\0';

        // Set the value to the property
        icalproperty_set_pollproperties(prop, value);

        // Call the function-under-test
        const char *result = icalproperty_get_pollproperties(prop);

        // Use the result in some way to avoid compiler optimizations
        if (result != NULL) {
            // Print the result for debugging purposes (optional)
            volatile size_t result_length = strlen(result);
            (void)result_length; // Use the result length to avoid optimization
        }

        // Free the allocated memory for value
        free(value);
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

    LLVMFuzzerTestOneInput_801(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
