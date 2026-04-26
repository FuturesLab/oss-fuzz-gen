#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for string operations
    if (size == 0) {
        return 0;
    }

    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_XLICCLUSTERCOUNT_PROPERTY);
    if (prop == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Call the function-under-test
    // The function expects a string, so pass the null-terminated data directly
    icalproperty_set_xlicclustercount(prop, null_terminated_data);

    // Additional operations to increase code coverage
    // Retrieve the property value to ensure it's set correctly
    const char *retrieved_value = icalproperty_get_xlicclustercount(prop);
    if (retrieved_value != NULL) {
        // Perform some operation with the retrieved value
        // This could be further processing or validation
        size_t retrieved_length = strlen(retrieved_value);
        if (retrieved_length > 0) {
            // Example: Check if the retrieved value starts with a specific prefix
            if (strncmp(retrieved_value, "PREFIX", 6) == 0) {
                // Do something if it matches
            }
        }
    }

    // Clean up
    icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_279(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
