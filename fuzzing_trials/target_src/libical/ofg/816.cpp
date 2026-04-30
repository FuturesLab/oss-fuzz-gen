#include <cstdint>  // Include the header for uint8_t
#include <cstdlib>  // Include the header for malloc and free
#include <cstring>  // Include the header for memcpy

extern "C" {
    #include "libical/ical.h"  // Include the necessary header for icalproperty_string_to_action
}

extern "C" int LLVMFuzzerTestOneInput_816(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for string processing
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test with the prepared string
    icalproperty_action action = icalproperty_string_to_action(inputString);

    // Clean up allocated memory
    free(inputString);

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

    LLVMFuzzerTestOneInput_816(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
