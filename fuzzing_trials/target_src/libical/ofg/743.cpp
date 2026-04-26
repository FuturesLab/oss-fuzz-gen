#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_743(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data to create an icalproperty
    icalproperty *property = icalproperty_new_from_string(inputData);

    // Check if the property was created successfully
    if (property != NULL) {
        // Call the function-under-test
        icalproperty_proximity proximity = icalproperty_get_proximity(property);

        // Clean up
        icalproperty_free(property);
    }

    // Free the allocated memory
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

    LLVMFuzzerTestOneInput_743(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
