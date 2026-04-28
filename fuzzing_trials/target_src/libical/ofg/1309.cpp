#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1309(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(buffer);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Call the function-under-test
        const char *permission = icalproperty_get_permission(prop);

        // Use the result in some way (e.g., print, log, etc.)
        // For fuzzing, we generally don't need to do anything with the result
        (void)permission;

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Free the buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_1309(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
