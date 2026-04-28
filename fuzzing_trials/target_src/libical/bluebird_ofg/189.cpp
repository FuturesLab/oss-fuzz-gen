#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include <cstring> // Include the header for memcpy

extern "C" {
    // Ensure all C functions and headers are wrapped in extern "C"
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) + sizeof(struct icaldurationtype)) {
        return 0; // Not enough data to form both structs
    }

    // Initialize icaltimetype and icaldurationtype from input data
    struct icaltimetype time;
    struct icaldurationtype duration;

    // Copy data into the structs
    memcpy(&time, data, sizeof(struct icaltimetype));
    memcpy(&duration, data + sizeof(struct icaltimetype), sizeof(struct icaldurationtype));

    // Call the function-under-test
    struct icaltimetype result = icalduration_extend(time, duration);

    // Optionally, further operations can be done on 'result' if needed

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

    LLVMFuzzerTestOneInput_189(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
