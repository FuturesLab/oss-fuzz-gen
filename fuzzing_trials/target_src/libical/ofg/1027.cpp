#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1027(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    // Copy data to input and null-terminate
    memcpy(input, data, size);
    input[size] = '\0';

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new_from_string(input);
    if (prop != NULL) {
        // Call the function-under-test
        const char *url = icalproperty_get_url(prop);

        // Use the result (url) if needed for further operations
        // For fuzzing purposes, we just ensure the function is called

        // Free the icalproperty object
        icalproperty_free(prop);
    }

    // Free allocated memory
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

    LLVMFuzzerTestOneInput_1027(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
