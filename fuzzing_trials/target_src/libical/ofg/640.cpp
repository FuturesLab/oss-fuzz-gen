#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_640(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate and initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *patchparameter = (char *)malloc(size + 1);
    if (patchparameter == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(patchparameter, data, size);
    patchparameter[size] = '\0';

    // Call the function-under-test
    icalproperty_set_patchparameter(prop, patchparameter);

    // Additional logic to ensure the function is exercised
    // Check if the patchparameter was set correctly
    const char *retrieved_patchparameter = icalproperty_get_patchparameter(prop);
    if (retrieved_patchparameter && strcmp(retrieved_patchparameter, patchparameter) == 0) {
        // Successfully set and retrieved the patchparameter
    }

    // Clean up
    free(patchparameter);
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

    LLVMFuzzerTestOneInput_640(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
