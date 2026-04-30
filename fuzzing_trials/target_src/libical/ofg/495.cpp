#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for strlen function

extern "C" {
    // Declare the necessary C functions and types
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
        ICAL_ERROR_LAST
    } icalerrorenum;

    const char *icalerror_strerror(icalerrorenum);
}

extern "C" int LLVMFuzzerTestOneInput_495(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract an icalerrorenum value
    if (size < sizeof(icalerrorenum)) {
        return 0;
    }

    // Cast the input data to icalerrorenum type
    icalerrorenum error_code = static_cast<icalerrorenum>(data[0] % ICAL_ERROR_LAST);

    // Call the function-under-test
    const char *error_str = icalerror_strerror(error_code);

    // Use the result to avoid compiler optimizations
    if (error_str) {
        // Do something trivial with error_str, like checking its length
        volatile size_t length = strlen(error_str);
        (void)length;
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

    LLVMFuzzerTestOneInput_495(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
