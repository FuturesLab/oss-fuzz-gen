#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_585(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data as a string
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Parse the input data to create an icalvalue
    // Using a default kind as icalvalue_new_from_string requires a kind
    icalvalue *value = icalvalue_new_from_string(ICAL_STRING_VALUE, input);

    // Ensure the value is not NULL
    if (value != NULL) {
        // Perform operations on the icalvalue to increase code coverage
        // For example, retrieve the kind and check it
        icalvalue_kind kind = icalvalue_isa(value);
        if (kind == ICAL_STRING_VALUE) {
            // Do something with the value to ensure it is processed
            const char *str = icalvalue_as_ical_string(value);
            if (str != NULL) {
                // Process the string representation
                size_t str_len = strlen(str);
                if (str_len > 0) {
                    // Simulate some processing
                    volatile size_t dummy = str_len;
                    (void)dummy;
                }
            }
        }

        // Clone the icalvalue
        icalvalue *cloned_value = icalvalue_clone(value);

        // Clean up the cloned value
        icalvalue_free(cloned_value);

        // Clean up the original value
        icalvalue_free(value);
    }

    // Clean up the input buffer
    delete[] input;

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

    LLVMFuzzerTestOneInput_585(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
