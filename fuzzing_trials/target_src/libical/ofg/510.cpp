#include <cstdint> // For uint8_t
#include <cstdlib> // For malloc, free
#include <cstring> // For memcpy, strlen

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_510(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data and ensure it's null-terminated.
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalproperty from the buffer.
    icalproperty *property = icalproperty_new_from_string(buffer);
    if (property != NULL) {
        // Call the function-under-test.
        const char *result = icalproperty_get_xlicmimeoptinfo(property);

        // Use the result in some way to avoid compiler optimizations removing the call.
        if (result != NULL) {
            // Just print the result length for demonstration purposes.
            (void)strlen(result);
        }

        // Clean up the icalproperty.
        icalproperty_free(property);
    }

    // Free the buffer.
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

    LLVMFuzzerTestOneInput_510(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
