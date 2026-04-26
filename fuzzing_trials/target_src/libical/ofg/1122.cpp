#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1122(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a meaningful string
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new_xlicerror("Initial Error");

    // Use the input data to create a null-terminated string
    char *xlicerror_str = (char *)malloc(size + 1);
    if (xlicerror_str == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(xlicerror_str, data, size);
    xlicerror_str[size] = '\0';

    // Call the function-under-test
    icalproperty_set_xlicerror(prop, xlicerror_str);

    // Additional function calls to increase code coverage
    const char *retrieved_error = icalproperty_get_xlicerror(prop);
    if (retrieved_error != NULL) {
        // Perform some operation with the retrieved error to ensure it's being processed
        size_t retrieved_length = strlen(retrieved_error);
        if (retrieved_length > 0) {
            // Do something with the length to avoid compiler optimizations
            (void)retrieved_length;
        }
    }

    // To increase code coverage, we can try parsing the property to a string and back
    const char *prop_str = icalproperty_as_ical_string(prop);
    if (prop_str != NULL) {
        icalproperty *parsed_prop = icalproperty_new_from_string(prop_str);
        if (parsed_prop != NULL) {
            // Clean up the newly created property
            icalproperty_free(parsed_prop);
        }
        // No need to free prop_str as it is managed by libical
    }

    // Clean up
    free(xlicerror_str);
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

    LLVMFuzzerTestOneInput_1122(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
