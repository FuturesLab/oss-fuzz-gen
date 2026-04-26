#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_916(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract two doubles for latitude and longitude
    if (size < 2 * sizeof(double)) {
        return 0;
    }

    // Extract latitude and longitude from the input data
    double latitude = *reinterpret_cast<const double*>(data);
    double longitude = *reinterpret_cast<const double*>(data + sizeof(double));

    // Create an icalgeotype with the extracted latitude and longitude
    icalgeotype geo;

    // Format the latitude and longitude as strings
    snprintf(geo.lat, sizeof(geo.lat), "%f", latitude);
    snprintf(geo.lon, sizeof(geo.lon), "%f", longitude);

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_geo(geo, NULL);

    // Clean up
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

    LLVMFuzzerTestOneInput_916(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
