#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <stdbool.h> // Include for bool type

extern "C" {
    #include "libical/ical.h" // Include the main libical header for access to all functionality
}

extern "C" int LLVMFuzzerTestOneInput_395(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalvalue
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0'; // Null-terminate the string

    // Determine the kind of icalvalue to create
    // For simplicity, we will use ICAL_STRING_VALUE, but this can be adjusted
    icalvalue_kind kind = ICAL_STRING_VALUE;

    // Parse the input data into an icalvalue
    icalvalue *value = icalvalue_new_from_string(kind, input_data);
    free(input_data);

    // Check if the icalvalue is valid
    if (value != NULL) {
        bool is_valid = icalvalue_is_valid(value);
        // Optionally, do something with is_valid
        // For example, log it or use it in further processing

        // Free the icalvalue
        icalvalue_free(value);
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

    LLVMFuzzerTestOneInput_395(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
