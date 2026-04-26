#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Include the necessary header for memcpy

// Include the necessary header for the function-under-test
extern "C" {
    #include "libical/icalproperty.h"
}

// Function-under-test
extern "C" bool icalproperty_isa_property(void *property);

extern "C" int LLVMFuzzerTestOneInput_611(const uint8_t *data, size_t size) {
    // Ensure data is not NULL and size is sufficient
    if (data == NULL || size < sizeof(void *)) {
        return 0;
    }

    // Allocate memory for a dummy property
    void *property = malloc(size);
    if (property == NULL) {
        return 0;
    }

    // Copy data to the allocated property
    memcpy(property, data, size);

    // Call the function-under-test
    bool result = icalproperty_isa_property(property);

    // Free the allocated memory
    free(property);

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

    LLVMFuzzerTestOneInput_611(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
