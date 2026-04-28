#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h> // Correctly include the libical header
}

extern "C" int LLVMFuzzerTestOneInput_898(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create a new icalproperty from the buffer
    icalproperty *prop = icalproperty_new_from_string(buffer);

    // If the property was created successfully, call the function-under-test
    if (prop != NULL) {
        struct icaltimetype due_time = icalproperty_get_due(prop);

        // Normally, you would do something with due_time here, but for fuzzing,
        // we are only interested in calling the function to check for crashes.

        // Clean up
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

    LLVMFuzzerTestOneInput_898(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
