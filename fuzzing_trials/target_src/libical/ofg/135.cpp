#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be used as a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *patchdelete_str = new char[size + 1];
    memcpy(patchdelete_str, data, size);
    patchdelete_str[size] = '\0';

    // Initialize an icalproperty
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Call the function-under-test
    icalproperty_set_patchdelete(property, patchdelete_str);

    // Clean up
    icalproperty_free(property);
    delete[] patchdelete_str;

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

    LLVMFuzzerTestOneInput_135(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
