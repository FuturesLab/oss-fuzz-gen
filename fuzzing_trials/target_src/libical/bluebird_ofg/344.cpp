#include <string.h>
#include <sys/stat.h>
#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_344(const uint8_t *data, size_t size) {
    // Call the function-under-test
    struct icaldurationtype duration = icaldurationtype_null_duration();

    // Since the function doesn't take any input parameters and returns a struct,
    // there's no need to manipulate `data` or `size`.

    // Use the returned duration struct for any further operations if necessary
    // For example, just printing the duration (though not necessary for fuzzing)
    icaldurationtype_as_ical_string(duration);

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

    LLVMFuzzerTestOneInput_344(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
