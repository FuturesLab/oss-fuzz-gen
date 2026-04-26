#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

extern "C" {
    #include <libical/ical.h>  // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_1123(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid empty string issues
    if (size == 0) {
        return 0;
    }

    // Create an icalproperty object with a valid property kind
    icalproperty *property = icalproperty_new(ICAL_XLICERROR_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Create a buffer for the error message, ensuring it's null-terminated
    char *error_message = (char *)malloc(size + 1);
    if (error_message == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(error_message, data, size);
    error_message[size] = '\0';

    // Call the function under test
    icalproperty_set_xlicerror(property, error_message);

    // Additional use of the property to increase code coverage
    const char *retrieved_error = icalproperty_get_xlicerror(property);
    if (retrieved_error != NULL) {
        // Perform some operation with retrieved_error if needed
        // For example, check if the retrieved error matches the input
        if (strcmp(retrieved_error, error_message) != 0) {
            // This branch will be taken if there's a mismatch
            // Perform additional operations or logging if needed
        }
    }

    // Additional operations to increase code coverage
    // For example, change the error message and check again
    char *new_error_message = (char *)malloc(size + 2);
    if (new_error_message != NULL) {
        memcpy(new_error_message, data, size);
        new_error_message[size] = '!';
        new_error_message[size + 1] = '\0';

        icalproperty_set_xlicerror(property, new_error_message);
        const char *new_retrieved_error = icalproperty_get_xlicerror(property);
        if (new_retrieved_error != NULL) {
            // Check if the new retrieved error matches the new input
            if (strcmp(new_retrieved_error, new_error_message) != 0) {
                // This branch will be taken if there's a mismatch
                // Perform additional operations or logging if needed
            }
        }

        free(new_error_message);
    }

    // Clean up
    free(error_message);
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

    LLVMFuzzerTestOneInput_1123(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
