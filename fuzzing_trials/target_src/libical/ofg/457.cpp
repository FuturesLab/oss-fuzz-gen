extern "C" {
    #include <stdlib.h>
    #include <string.h>
    // Declare the function prototype if the header is missing
    typedef enum icalerrorenum {
        ICAL_NO_ERROR = 0,
        ICAL_BADARG_ERROR,
        ICAL_NEWFAILED_ERROR,
        ICAL_ALLOCATION_ERROR,
        ICAL_USAGE_ERROR,
        ICAL_PARSE_ERROR,
        ICAL_INTERNAL_ERROR,
        ICAL_ERROR_UNKNOWN
    } icalerrorenum;

    icalerrorenum icalerror_error_from_string(const char *str);
}

#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_457(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated before passing it to the function
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // Memory allocation failed, exit gracefully
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalerrorenum result = icalerror_error_from_string(inputString);

    // Clean up
    free(inputString);

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

    LLVMFuzzerTestOneInput_457(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
