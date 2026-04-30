#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Include the standard I/O library for printf

extern "C" {
    #include <libical/icalproperty.h> // Assuming libical provides this header
}

extern "C" int LLVMFuzzerTestOneInput_591(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely convert to a string
    if (size == 0) return 0; // Early return if size is zero to ensure non-null input

    char *input = (char *)malloc(size + 1);
    if (input == NULL) return 0; // Check for allocation failure
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_itipversion(input);

    // Additional logic to ensure the function is exercised
    if (prop != NULL) {
        // Perform operations on the property to ensure coverage
        const char *version = icalproperty_get_itipversion(prop);
        if (version != NULL) {
            // Use the version string in some way
            printf("iTIP version: %s\n", version);
        }
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

    LLVMFuzzerTestOneInput_591(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
