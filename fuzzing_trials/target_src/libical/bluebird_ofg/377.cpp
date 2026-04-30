#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"
    
    struct icaldurationtype icalproperty_get_refreshinterval(const icalproperty *);
}

extern "C" int LLVMFuzzerTestOneInput_377(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a property
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Call the function-under-test
    struct icaldurationtype duration = icalproperty_get_refreshinterval(prop);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_377(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
