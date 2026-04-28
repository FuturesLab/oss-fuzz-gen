#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>  // Correct header for icalproperty
}

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Initialize variables
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    char *patchdelete_str = nullptr;

    // Ensure the data is not empty
    if (size > 0) {
        // Allocate memory for patchdelete_str and copy data into it
        patchdelete_str = new char[size + 1];
        memcpy(patchdelete_str, data, size);
        patchdelete_str[size] = '\0';  // Null-terminate the string
    } else {
        // Provide a default non-NULL string
        patchdelete_str = new char[1];
        patchdelete_str[0] = '\0';
    }

    // Call the function under test
    icalproperty_set_patchdelete(property, patchdelete_str);

    // Clean up
    delete[] patchdelete_str;
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

    LLVMFuzzerTestOneInput_136(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
