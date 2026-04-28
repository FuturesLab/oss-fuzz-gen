#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_705(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalproperty from the input string
    icalproperty *property = icalproperty_new_from_string(inputData);
    free(inputData);

    if (property != NULL) {
        // Call the function-under-test
        const char *result = icalproperty_get_value_as_string(property);

        // Optionally, you can do something with the result
        // For example, print it or check its validity
        if (result != NULL) {
            // Do something with the result if needed
        }

        // Clean up
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_705(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
