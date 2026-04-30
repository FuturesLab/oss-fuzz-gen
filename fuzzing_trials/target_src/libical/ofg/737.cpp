#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_737(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';  // Null-terminate the string

    // Create an icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != NULL) {
        // Call the function-under-test
        const char *result = icalproperty_get_tzidaliasof(prop);

        // Use the result in some way to avoid compiler optimizations
        if (result != NULL) {
            // For example, print the result (in real fuzzing, this would not be needed)
            printf("TZID Alias Of: %s\n", result);
        }

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_737(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
