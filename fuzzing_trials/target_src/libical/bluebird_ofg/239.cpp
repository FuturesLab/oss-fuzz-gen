#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int intValue;
    memcpy(&intValue, data, sizeof(int));

    // Prepare a non-null void pointer with a valid icalvalue
    icalvalue *value = icalvalue_new_integer(intValue);
    if (!value) {
        return 0;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_repeat(intValue, value, nullptr);

    // Clean up if necessary
    if (property != nullptr) {
        icalproperty_free(property);
    }
    icalvalue_free(value);

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

    LLVMFuzzerTestOneInput_239(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
