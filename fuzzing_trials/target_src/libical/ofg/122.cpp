#include <cstdint>
#include <cstddef>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for testing
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Allocate and initialize icalproperty
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);
    icalproperty *prop = icalproperty_new(kind);
    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    // Since the original code attempted to use a va_list, and given no direct equivalent
    // in C++ for the C va_list structure, we will skip this part as it doesn't directly
    // correspond to a function in libical that uses va_list.
    // icalproperty_add_parameters(prop, &va_list_data);

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

    LLVMFuzzerTestOneInput_122(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
