#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_626(const uint8_t *data, size_t size) {
    // Ensure size is non-zero for creating a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *x_value = (char *)malloc(size + 1);
    if (x_value == NULL) {
        return 0;
    }
    memcpy(x_value, data, size);
    x_value[size] = '\0';

    // Create a new icalproperty object
    icalproperty *property = icalproperty_new(ICAL_X_PROPERTY);
    if (property == NULL) {
        free(x_value);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_x(property, x_value);

    // Clean up
    icalproperty_free(property);
    free(x_value);

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

    LLVMFuzzerTestOneInput_626(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
