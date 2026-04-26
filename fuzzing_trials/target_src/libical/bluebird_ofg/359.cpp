#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_359(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to fill the icaldurationtype structure
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Cast the input data to an icaldurationtype pointer
    const struct icaldurationtype *duration = reinterpret_cast<const struct icaldurationtype *>(data);

    // Call the function-under-test
    icalproperty *property = icalproperty_new_refreshinterval(*duration);

    // Clean up the created property to prevent memory leaks
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_359(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
