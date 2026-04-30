#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_454(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *x_name = (char *)malloc(size + 1);
    if (!x_name) {
        return 0;
    }
    memcpy(x_name, data, size);
    x_name[size] = '\0';

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_X_PROPERTY);
    if (!prop) {
        free(x_name);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_x_name(prop, x_name);

    // Additional logic to increase code coverage
    const char *retrieved_x_name = icalproperty_get_x_name(prop);
    if (retrieved_x_name) {
        // Optionally, perform operations on the retrieved name
        // For example, compare it with the original input
        if (strcmp(retrieved_x_name, x_name) != 0) {
            // Handle mismatch if needed
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(x_name);

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

    LLVMFuzzerTestOneInput_454(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
