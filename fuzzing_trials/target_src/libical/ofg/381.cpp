#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the libical headers
}

extern "C" int LLVMFuzzerTestOneInput_381(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for string operations
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new_patchdelete(null_terminated_data);

    // Check if the property was created successfully
    if (property != NULL) {
        // Call the function-under-test
        const char *result = icalproperty_get_patchdelete(property);

        // Check the result to ensure it is not null
        if (result != NULL) {
            // Perform operations with the result if needed
            // This ensures that the function is being tested with meaningful input
            // For example, we can log or analyze the result
        }

        // Clean up
        icalproperty_free(property);
    }

    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_381(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
