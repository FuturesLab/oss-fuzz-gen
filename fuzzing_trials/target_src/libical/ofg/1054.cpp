#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    #include <libical/ical.h> // Ensure libical headers are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_1054(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to store the data
    char *buffer = new char[size + 1];
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Create an icalproperty from the buffer
    icalproperty *prop = icalproperty_new_from_string(buffer);
    
    // If the property is successfully created, call the function-under-test
    if (prop != NULL) {
        const char *target = icalproperty_get_target(prop);
        // Use the target in some way to avoid compiler optimizations
        if (target != NULL) {
            // For fuzzing purposes, we do not need to do anything with the target
        }
        
        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_1054(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
