#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>

// Wrap the libical includes with extern "C" since libical is a C library
extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure we have enough data to derive an enumeration value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data to use as a proximity value
    int proximity_value = *(reinterpret_cast<const int*>(data));

    // Cast the integer to the correct enumeration type from libical
    icalproperty_proximity proximity_enum =
        static_cast<icalproperty_proximity>(proximity_value);

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_proximity(proximity_enum, NULL);

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

    LLVMFuzzerTestOneInput_42(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
