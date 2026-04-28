#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include the standard library for malloc and free

// Wrap the C library includes and function declarations with extern "C"
extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the libical headers
}

extern "C" int LLVMFuzzerTestOneInput_340(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Use part of the data as a string for the restriction
    size_t str_size = size - 1;
    char *restriction = (char *)malloc(str_size + 1);
    if (restriction == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(restriction, data, str_size);
    restriction[str_size] = '\0';

    // Call the function-under-test
    icalproperty_set_restriction(prop, restriction);

    // Clean up
    free(restriction);
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

    LLVMFuzzerTestOneInput_340(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
