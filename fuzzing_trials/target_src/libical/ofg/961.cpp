#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalparameter.h>
}

extern "C" int LLVMFuzzerTestOneInput_961(const uint8_t *data, size_t size) {
    // Ensure the data is non-zero to avoid null dereference
    if (size > 0) {
        // Create a string from the input data
        char *input = (char *)malloc(size + 1);
        if (input == NULL) {
            return 0; // Memory allocation failed
        }
        memcpy(input, data, size);
        input[size] = '\0'; // Null-terminate the string

        // Parse the input data into an icalparameter
        icalparameter *param = icalparameter_new_from_string(input);
        free(input);

        if (param != NULL) {
            // Use the parameter to invoke functions under test
            icalparameter_kind kind = icalparameter_isa(param);

            // Call the function-under-test
            icalparameter *result = icalparameter_new(kind);

            // Use the result to prevent any compiler optimizations
            if (result != NULL) {
                icalparameter_free(result);
            }

            // Clean up
            icalparameter_free(param);
        }
    }

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

    LLVMFuzzerTestOneInput_961(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
