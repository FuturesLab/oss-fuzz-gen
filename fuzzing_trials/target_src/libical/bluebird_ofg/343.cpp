#include <string.h>
#include <sys/stat.h>
#include <cstdint>  // Include the standard library for uint8_t

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
    // Since the function icaltimezone_free_builtin_timezones does not take any parameters,
    // we do not need to use the input data in this case. We simply call the function.

    // Call the function-under-test
    icaltimezone_free_builtin_timezones();

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

    LLVMFuzzerTestOneInput_343(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
