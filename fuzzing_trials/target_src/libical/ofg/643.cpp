#include <stdint.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_643(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to prevent creating an invalid string
    if (size == 0) return 0;

    // Allocate memory for the input string and ensure it's null-terminated
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Create an icalproperty from the input string
    icalproperty *prop = icalproperty_new_from_string(input);

    // Call the function-under-test if the property was successfully created
    if (prop != NULL) {
        const char *queryid = icalproperty_get_queryid(prop);
        // Use queryid in some way to prevent compiler optimizations from removing the call
        if (queryid) {
            // For example, print it or perform a simple operation
            (void)queryid[0];
        }
        icalproperty_free(prop);
    }

    // Clean up
    delete[] input;
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

    LLVMFuzzerTestOneInput_643(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
