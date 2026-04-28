#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

extern "C" {
    #include <libical/icalproperty.h>  // Include the correct libical header for icalproperty functions
}

extern "C" int LLVMFuzzerTestOneInput_599(const uint8_t *data, size_t size) {
    // Ensure the size of the data is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the data
    char *patchversion = (char *)malloc(size + 1);
    if (patchversion == NULL) {
        return 0; // Handle memory allocation failure
    }
    memcpy(patchversion, data, size);
    patchversion[size] = '\0';

    // Attempt to create an icalproperty object with a specific property type
    icalproperty *prop = icalproperty_new_patchversion(patchversion);
    if (prop == NULL) {
        free(patchversion);
        return 0; // Handle property creation failure
    }

    // Additional interaction with the icalproperty object to increase code coverage
    const char *retrieved_patchversion = icalproperty_get_patchversion(prop);
    if (retrieved_patchversion != NULL) {
        // Compare the set and retrieved values to ensure they match
        if (strcmp(patchversion, retrieved_patchversion) != 0) {
            // Log a mismatch if needed (for debugging purposes)
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(patchversion);

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

    LLVMFuzzerTestOneInput_599(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
