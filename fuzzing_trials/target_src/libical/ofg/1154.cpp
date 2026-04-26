#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1154(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a new icalproperty with a dummy value
    icalproperty *prop = icalproperty_new(ICAL_RECURACCEPTED_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Set the input data as the value to the icalproperty
    icalproperty_set_recuraccepted(prop, input_data);

    // Call the function-under-test
    const char *result = icalproperty_get_recuraccepted(prop);

    // Use the result to avoid compiler optimizations
    if (result) {
        // Do something with result if needed
    }

    // Clean up
    free(input_data);
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

    LLVMFuzzerTestOneInput_1154(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
