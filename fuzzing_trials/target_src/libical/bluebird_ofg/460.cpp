#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_460(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the input data and ensure it's null-terminated
    char *inputData = static_cast<char *>(malloc(size + 1));
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data to create an icalproperty
    icalproperty *property = icalproperty_new_from_string(inputData);
    if (property != NULL) {
        // Call the function-under-test
        int result = icalproperty_get_maxresultssize(property);

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

    LLVMFuzzerTestOneInput_460(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
