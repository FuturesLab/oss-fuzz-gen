#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure there is enough data to select a valid enum value
    if (size < sizeof(int)) {
        return 0;
    }

    // Map the input data to an enumeration value
    int enum_index = data[0] % 3; // Assuming there are 3 enum values
    icalproperty_transp transp_value;

    // Assign a valid enum value based on the mapped index
    switch (enum_index) {
        case 0:
            transp_value = ICAL_TRANSP_OPAQUE;
            break;
        case 1:
            transp_value = ICAL_TRANSP_TRANSPARENT;
            break;
        default:
            transp_value = ICAL_TRANSP_X;
            break;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_transp(transp_value, NULL);

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

    LLVMFuzzerTestOneInput_38(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
