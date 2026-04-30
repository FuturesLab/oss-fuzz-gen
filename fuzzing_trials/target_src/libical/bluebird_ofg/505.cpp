#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_505(const uint8_t *data, size_t size) {
    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalvalue from the buffer
    icalvalue *value = icalvalue_new_from_string(ICAL_STRING_VALUE, buffer);
    if (value != NULL) {
        // Call the function-under-test
        icalproperty *parent = icalvalue_get_parent(value);

        // Normally, you would do something with the parent here
        // For fuzzing, we just ensure the function is called

        // Free the icalvalue
        icalvalue_free(value);
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

    LLVMFuzzerTestOneInput_505(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
