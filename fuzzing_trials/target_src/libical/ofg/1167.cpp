#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1167(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_XLICMIMEFILENAME_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    icalproperty_set_xlicmimefilename(property, filename);

    // Additional operations to increase code coverage
    // Retrieve the filename to ensure the set operation was successful
    const char *retrieved_filename = icalproperty_get_xlicmimefilename(property);
    if (retrieved_filename != NULL) {
        // Compare retrieved filename with the original to ensure correctness
        if (strcmp(filename, retrieved_filename) != 0) {
            // If they do not match, there might be an issue
            abort();
        }
    }

    // Clean up
    free(filename);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_1167(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
