#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure there's enough data to initialize icalpropiter
    if (size < sizeof(icalpropiter)) {
        return 0;
    }

    // Initialize icalpropiter from the input data
    icalpropiter iter;
    memcpy(&iter, data, sizeof(icalpropiter));

    // Call the function-under-test
    bool is_valid = icalpropiter_is_valid(&iter);

    // Use the result in some way to prevent compiler optimizations
    if (is_valid) {
        // Do something if valid (no-op)
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_49(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
