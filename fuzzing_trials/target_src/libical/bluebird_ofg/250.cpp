#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to fill an icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Cast the input data to an icaltimetype structure
    struct icaltimetype time = *(struct icaltimetype *)data;

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_due(time, NULL);

    // Clean up the created property to avoid memory leaks
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

    LLVMFuzzerTestOneInput_250(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
