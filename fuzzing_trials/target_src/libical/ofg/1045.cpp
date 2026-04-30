#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_1045(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Create a new icalproperty from the input string
    icalproperty *prop = icalproperty_new_from_string(input);
    if (prop != NULL) {
        // Call the function-under-test
        const char *filename = icalproperty_get_xlicmimefilename(prop);

        // For fuzzing purposes, we might want to do something with the result
        // Here, we just check if it's not null
        if (filename != NULL) {
            // Do something with the filename, if needed
        }

        // Clean up
        icalproperty_free(prop);
    }

    // Free the allocated input string
    free(input);

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

    LLVMFuzzerTestOneInput_1045(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
