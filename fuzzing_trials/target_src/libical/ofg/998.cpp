#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_998(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icalproperty object
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = new char[size + 1];
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Create an icalproperty object from the buffer
    icalproperty *property = icalproperty_new_from_string(buffer);

    // Ensure the property is not NULL before calling the function
    if (property != NULL) {
        // Call the function-under-test
        const char *deny_value = icalproperty_get_deny(property);

        // Optionally do something with deny_value, e.g., print or log
        // For fuzzing purposes, we typically don't need to process the output
    }

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
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

    LLVMFuzzerTestOneInput_998(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
