#include <cstdint>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalerror.h>
}

extern "C" int LLVMFuzzerTestOneInput_1099(const uint8_t *data, size_t size) {
    // Initialize the icalerror system
    icalerror_clear_errno();

    // Call the function-under-test
    icalerror_set_error_state(ICAL_PARSE_ERROR, ICAL_ERROR_FATAL);

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

    LLVMFuzzerTestOneInput_1099(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
