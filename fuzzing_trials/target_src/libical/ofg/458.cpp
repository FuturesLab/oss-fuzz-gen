#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy

extern "C" {
    // Declare the function from the C library
    typedef enum icalerrorenum {
        ICAL_NO_ERROR = 0, // Example enum value, replace with actual values from the library
        ICAL_BADARG_ERROR,
        ICAL_NEWFAILED_ERROR,
        ICAL_ALLOCATION_ERROR,
        ICAL_PARSE_ERROR,
        ICAL_INTERNAL_ERROR
    } icalerrorenum;

    icalerrorenum icalerror_error_from_string(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_458(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated for the string function
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and copy the data
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    icalerrorenum result = icalerror_error_from_string(inputString);

    // Clean up
    delete[] inputString;

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

    LLVMFuzzerTestOneInput_458(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
