#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memcpy

// Wrap C headers and functions in extern "C" to ensure proper linkage
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1082(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for initializing icalgeotype
    if (size < sizeof(double) * 2) {
        return 0;
    }

    // Initialize icalproperty
    icalproperty *property = icalproperty_new(ICAL_GEO_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Initialize icalgeotype with values from the input data
    struct icalgeotype geo;
    // Use memcpy to safely copy data into the geo structure
    memcpy(&geo.lat, data, sizeof(double));
    memcpy(&geo.lon, data + sizeof(double), sizeof(double));

    // Call the function-under-test
    icalproperty_set_geo(property, geo);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_1082(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
