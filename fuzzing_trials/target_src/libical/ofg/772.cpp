#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_772(const uint8_t *data, size_t size) {
    // Ensure size is non-zero and data is not NULL
    if (size == 0 || data == nullptr) {
        return 0;
    }

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RECUREXPAND_PROPERTY);

    // Ensure the property was created successfully
    if (prop == nullptr) {
        return 0;
    }

    // Convert the input data to a string, ensuring it's null-terminated
    char *recurexpand_str = (char *)malloc(size + 1);
    if (recurexpand_str == nullptr) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(recurexpand_str, data, size);
    recurexpand_str[size] = '\0';

    // Call the function under test
    icalproperty_set_recurexpand(prop, recurexpand_str);

    // Clean up
    free(recurexpand_str);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_772(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
