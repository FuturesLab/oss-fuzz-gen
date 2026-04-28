#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_512(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *buffer = new char[size + 1];
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Create an icalproperty from the buffer
    icalproperty *prop = icalproperty_new_from_string(buffer);

    // Ensure the property is not NULL
    if (prop != NULL) {
        // Call the function-under-test
        const char *name = icalproperty_get_name(prop);

        // Use the name in some way to avoid compiler optimizations
        if (name != NULL) {
            // Print the name for debugging purposes (optional)
            // printf("Property Name: %s\n", name);
        }

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Clean up the buffer
    delete[] buffer;

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

    LLVMFuzzerTestOneInput_512(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
