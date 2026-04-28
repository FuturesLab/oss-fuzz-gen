#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_recurrenceid(time, NULL);

    // Clean up if the function returns a non-null pointer
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

    LLVMFuzzerTestOneInput_241(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
