#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_350(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize icaltimetype from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalproperty_vanew_tzuntil with icalproperty_new_lastmodified
    icalproperty *prop = icalproperty_new_lastmodified(time);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

    // Clean up if a property was created
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_350(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
