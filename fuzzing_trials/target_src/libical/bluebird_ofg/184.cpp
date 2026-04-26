#include <string.h>
#include <sys/stat.h>
#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t
#include <cstring>  // For strlen

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to prevent overflows in string functions
    if (size == 0 || data[size - 1] != '\0') {
        return 0; // Exit early if data is empty or not null-terminated
    }

    // Initialize a memory context
    icalproperty *prop = icalproperty_new_from_string((const char *)data);

    // Ensure the property is not NULL before calling the function
    if (prop != NULL) {
        // Call the function-under-test
        icalproperty_proximity proximity = icalproperty_get_proximity(prop);

        // Use the proximity value in some way to prevent compiler optimizations from removing the call
        if (proximity == ICAL_PROXIMITY_NONE) {
            // Do something trivial
            (void)proximity;
        }

        // Clean up
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

    LLVMFuzzerTestOneInput_184(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
