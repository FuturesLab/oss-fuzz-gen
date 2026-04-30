#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1265(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Create an icalproperty from the input string
    icalproperty *prop = icalproperty_new_from_string(input);
    if (prop != NULL) {
        // Call the function-under-test
        const char *description = icalproperty_get_description(prop);

        // Use the description in some way to prevent compiler optimizations
        if (description != NULL) {
            // For fuzzing purposes, we can simply ensure the string is accessed
            volatile char first_char = description[0];
            (void)first_char;
        }

        // Clean up
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_1265(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
