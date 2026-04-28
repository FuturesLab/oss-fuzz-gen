#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a null-terminated string
    if (size < 1) return 0;

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ITIPVERSION_PROPERTY);
    if (prop == NULL) return 0;

    // Create a null-terminated string from the input data
    char *itipversion = (char *)malloc(size + 1);
    if (itipversion == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(itipversion, data, size);
    itipversion[size] = '\0';

    // Call the function-under-test
    icalproperty_set_itipversion(prop, itipversion);

    // Check if the property was set correctly
    const char *retrieved_version = icalproperty_get_itipversion(prop);
    if (retrieved_version != NULL) {
        // Perform some operation to ensure the function is utilized
        if (strcmp(retrieved_version, itipversion) == 0) {
            // Successfully set and retrieved the same version
        }
    }

    // Clean up
    free(itipversion);
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

    LLVMFuzzerTestOneInput_141(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
