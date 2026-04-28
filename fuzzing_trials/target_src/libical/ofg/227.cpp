#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid string for icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = new char[size + 1];
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalproperty object from the string
    icalproperty *prop = icalproperty_new_from_string(inputData);

    // Ensure that the property is not NULL
    if (prop != NULL) {
        // Call the function-under-test
        int priority = icalproperty_get_priority(prop);

        // Optionally, use the result to prevent compiler optimizations
        (void)priority;

        // Free the icalproperty object
        icalproperty_free(prop);
    }

    // Clean up
    delete[] inputData;

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

    LLVMFuzzerTestOneInput_227(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
