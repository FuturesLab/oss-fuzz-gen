#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>  // Correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_1335(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold a null-terminated string
    char buffer[size + 1];
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(buffer);

    if (prop != NULL) {
        // Call the function-under-test
        const char *x_name = icalproperty_get_x_name(prop);

        // Optionally, do something with x_name, like printing or logging
        // printf("X-Name: %s\n", x_name);

        // Clean up the created icalproperty
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_1335(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
