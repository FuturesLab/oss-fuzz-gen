#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1284(const uint8_t *data, size_t size) {
    // Define all possible values for icalerrorenum and icalerrorstate
    icalerrorenum errorEnums[] = {
        ICAL_BADARG_ERROR,
        ICAL_NEWFAILED_ERROR,
        ICAL_ALLOCATION_ERROR,
        ICAL_MALFORMEDDATA_ERROR,
        ICAL_PARSE_ERROR,
        ICAL_INTERNAL_ERROR,
        ICAL_FILE_ERROR,
        ICAL_USAGE_ERROR,
        ICAL_UNIMPLEMENTED_ERROR,
        ICAL_NO_ERROR
    };

    icalerrorstate errorStates[] = {
        ICAL_ERROR_FATAL,
        ICAL_ERROR_DEFAULT,
        ICAL_ERROR_NONFATAL
    };

    // Iterate over all combinations of errorEnums and errorStates
    for (size_t i = 0; i < sizeof(errorEnums) / sizeof(errorEnums[0]); ++i) {
        for (size_t j = 0; j < sizeof(errorStates) / sizeof(errorStates[0]); ++j) {
            icalerror_set_error_state(errorEnums[i], errorStates[j]);
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

    LLVMFuzzerTestOneInput_1284(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
