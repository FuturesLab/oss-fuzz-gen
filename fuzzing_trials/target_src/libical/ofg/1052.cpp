#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_1052(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C string
    if (size == 0) {
        return 0; // Exit early if size is zero to avoid unnecessary operations
    }

    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_query(cstr);

    // Check if the property is NULL and handle it
    if (property != NULL) {
        // Perform additional operations on the property to increase code coverage
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind != ICAL_NO_PROPERTY) {
            // Optionally, you can add more operations based on the kind of property
        }
        icalproperty_free(property);
    }

    free(cstr);

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

    LLVMFuzzerTestOneInput_1052(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
