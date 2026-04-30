#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_862(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalproperty object
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty object from the input data
    // Using icalproperty_new_from_string to create a property from a string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }

    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    icalproperty *property = icalproperty_new_from_string(inputData);

    if (property != NULL) {
        // Call the function under test
        struct icaltimetype result = icalproperty_get_tzuntil(property);

        // Clean up the icalproperty object
        icalproperty_free(property);
    }

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

    LLVMFuzzerTestOneInput_862(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
