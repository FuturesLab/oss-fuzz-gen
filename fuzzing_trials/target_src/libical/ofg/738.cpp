#include <cstdint>  // Include for uint8_t
#include <cstdlib>  // Include for malloc and free
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_738(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input data and ensure it's null-terminated
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }

    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != NULL) {
        // Call the function-under-test
        const char *result = icalproperty_get_tzidaliasof(prop);

        // Use the result to prevent compiler optimizations (if necessary)
        if (result != NULL) {
            // Do something with the result, e.g., print it or log it
            // This is just to ensure the result is used
            (void)result;
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

    LLVMFuzzerTestOneInput_738(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
