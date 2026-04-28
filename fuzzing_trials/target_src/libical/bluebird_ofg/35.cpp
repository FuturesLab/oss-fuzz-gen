#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Added for memcpy

extern "C" {
    #include "/src/libical/src/libical/icalparameter.h" // Corrected include for libical
    #include "/src/libical/src/libical/icalderivedparameter.h" // Include the derived header for the complete type
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Ensure we have enough data to initialize icalparameter
    if (size == 0) {
        return 0;
    }

    // Null-terminate the input data to prevent overflow in string functions
    char *null_terminated_data = (char*)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalparameter object from the input data
    icalparameter *param = icalparameter_new_from_string(null_terminated_data);
    if (param == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Call the function-under-test
    icalparameter *result = icalparameter_new_from_string(null_terminated_data);

    // Free the allocated memory for param
    icalparameter_free(param);

    // Assume result needs to be freed if not NULL
    if (result != NULL) {
        icalparameter_free(result);
    }

    // Free the null-terminated data
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

    LLVMFuzzerTestOneInput_35(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
