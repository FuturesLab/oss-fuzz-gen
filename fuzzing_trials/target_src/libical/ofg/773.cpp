#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include <libical/ical.h> // Assuming the correct path and library name
}

extern "C" int LLVMFuzzerTestOneInput_773(const uint8_t *data, size_t size) {
    // Ensure size is large enough to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *recurexpand_str = (char *)malloc(size + 1);
    if (recurexpand_str == NULL) {
        return 0;
    }
    memcpy(recurexpand_str, data, size);
    recurexpand_str[size] = '\0';

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        free(recurexpand_str);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_recurexpand(prop, recurexpand_str);

    // Clean up
    icalproperty_free(prop);
    free(recurexpand_str);

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

    LLVMFuzzerTestOneInput_773(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
