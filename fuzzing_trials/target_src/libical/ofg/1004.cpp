#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1004(const uint8_t *data, size_t size) {
    // Ensure the input data is non-empty
    if (size == 0) {
        return 0;
    }

    // Create a buffer to hold the null-terminated string
    char *prodid = new char[size + 1];
    memcpy(prodid, data, size);
    prodid[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_new_prodid(prodid);

    // Additional operations to ensure code coverage
    if (property != NULL) {
        // Access some properties of the created icalproperty to ensure it is being used
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind == ICAL_PRODID_PROPERTY) {
            const char* prodid_value = icalproperty_get_prodid(property);
            if (prodid_value) {
                // Log or perform operations with prodid_value
                // For example, calculate its length or perform string operations
                size_t prodid_length = strlen(prodid_value);
                if (prodid_length > 0) {
                    // Perform additional operations if needed
                    // This ensures that different lengths and contents are tested
                }
            }
        }
        icalproperty_free(property);
    }
    delete[] prodid;

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

    LLVMFuzzerTestOneInput_1004(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
