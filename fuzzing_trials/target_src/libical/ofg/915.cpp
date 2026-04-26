#include <cstdint>  // For uint8_t
#include <cstring>  // For memcpy
#include <cstdio>   // For snprintf

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_915(const uint8_t *data, size_t size) {
    if (size < sizeof(double) * 2) {
        // Not enough data to extract latitude and longitude
        return 0;
    }

    // Extract latitude and longitude from the input data
    double latitude = 0.0;
    double longitude = 0.0;
    
    // Ensure the data is interpreted correctly as doubles
    memcpy(&latitude, data, sizeof(double));
    memcpy(&longitude, data + sizeof(double), sizeof(double));

    // Create an icalgeotype with the extracted values
    struct icalgeotype geo;
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

    LLVMFuzzerTestOneInput_915(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
