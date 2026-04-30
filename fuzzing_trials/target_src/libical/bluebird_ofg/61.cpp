#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to perform meaningful operations
    if (size < 1) {
        return 0;
    }

    // Initialize an icalcomponent from the input data
    icalcomponent *component = icalcomponent_vanew(
        ICAL_VCALENDAR_COMPONENT, 
        icalproperty_new_version("2.0"),
        icalproperty_new_prodid("-//Sample Corp//NONSGML Event//EN"),
        0);

    // Cast the first byte of data to icalproperty_kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);

    // Call the function-under-test
    icalproperty *property = icalcomponent_get_first_property(component, kind);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_61(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
