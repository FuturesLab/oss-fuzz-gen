#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1034(const uint8_t *data, size_t size) {
    // Create a temporary buffer to store the input data as a null-terminated string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalproperty
    icalproperty *property = icalproperty_new_from_string(inputData);

    // Ensure the property is not NULL before calling the function-under-test
    if (property != NULL) {
        // Call the function-under-test
        const char *result = icalproperty_get_recurexpand(property);

        // Optionally, you can perform additional checks or operations on the result here

        // Free the icalproperty after use
        icalproperty_free(property);
    }

    // Free the allocated buffer
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

    LLVMFuzzerTestOneInput_1034(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
