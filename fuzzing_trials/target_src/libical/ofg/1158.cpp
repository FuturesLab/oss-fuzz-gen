#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Declare the necessary functions and types from the libical project
    typedef enum icalerrorenum {
        ICAL_NO_ERROR = 0,
        ICAL_BADARG_ERROR,
        ICAL_NEWFAILED_ERROR,
        ICAL_ALLOCATION_ERROR,
        ICAL_MALFORMEDDATA_ERROR,
        ICAL_PARSE_ERROR,
        ICAL_INTERNAL_ERROR,
        ICAL_FILE_ERROR,
        ICAL_USAGE_ERROR,
        ICAL_UNIMPLEMENTED_ERROR,
        ICAL_UNKNOWN_ERROR,
        ICAL_ERROR_UNKNOWN
    } icalerrorenum;

    void icalerror_set_errno(icalerrorenum error);
}

extern "C" int LLVMFuzzerTestOneInput_1158(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a valid icalerrorenum value
    if (size < sizeof(icalerrorenum)) {
        return 0;
    }

    // Extract an icalerrorenum value from the input data
    icalerrorenum error_enum = static_cast<icalerrorenum>(data[0] % ICAL_ERROR_UNKNOWN);

    // Call the function-under-test with the extracted error_enum
    icalerror_set_errno(error_enum);

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

    LLVMFuzzerTestOneInput_1158(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
