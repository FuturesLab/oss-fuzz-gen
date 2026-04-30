#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this for memcpy
#include <libical/ical.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Create an icalproperty from the input string
    icalproperty *property = icalproperty_new_from_string(inputString);
    if (property != NULL) {
        // Call the function-under-test
        struct icaltriggertype trigger = icalproperty_get_trigger(property);

        // Clean up
        icalproperty_free(property);
    }

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

    LLVMFuzzerTestOneInput_261(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
