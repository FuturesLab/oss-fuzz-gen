#include <string.h>
#include <sys/stat.h>
#include <cstdint> // Include standard library for uint8_t

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a valid enumeration value
    if (size < 1) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_taskmode taskmode = static_cast<icalproperty_taskmode>(data[0] % 3);

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_taskmode(taskmode, NULL);

    // Clean up if a property was created
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

    LLVMFuzzerTestOneInput_39(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
