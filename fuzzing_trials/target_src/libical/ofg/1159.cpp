#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1159(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Extract the first byte from the data to use as the error enum value
    icalerrorenum error_enum = static_cast<icalerrorenum>(data[0] % ICAL_ERROR_UNKNOWN);

    // Call the function-under-test
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

    LLVMFuzzerTestOneInput_1159(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
