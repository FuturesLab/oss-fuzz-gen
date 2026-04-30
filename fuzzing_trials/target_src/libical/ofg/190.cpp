#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) return 0;

    // Allocate memory for the icalproperty
    icalproperty *property = icalproperty_new(ICAL_XLICMIMEOPTINFO_PROPERTY);
    if (property == NULL) return 0;

    // Create a null-terminated string from the input data
    char *xlicmimeoptinfo = (char *)malloc(size + 1);
    if (xlicmimeoptinfo == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(xlicmimeoptinfo, data, size);
    xlicmimeoptinfo[size] = '\0';

    // Call the function-under-test
    icalproperty_set_xlicmimeoptinfo(property, xlicmimeoptinfo);

    // Additional operations to increase code coverage
    const char *retrieved_info = icalproperty_get_xlicmimeoptinfo(property);
    if (retrieved_info != NULL) {
        // Perform operations on the retrieved info
        size_t retrieved_length = strlen(retrieved_info);
        
        // Check if the retrieved info matches the input
        if (retrieved_length == size && memcmp(retrieved_info, xlicmimeoptinfo, size) == 0) {
            // If it matches, perform additional operations
            (void)retrieved_length;
        } else {
            // If it doesn't match, handle the discrepancy
            (void)retrieved_length;
        }
    } else {
        // Handle the case where retrieved_info is NULL
    }

    // Clean up
    free(xlicmimeoptinfo);
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

    LLVMFuzzerTestOneInput_190(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
