#include <cstdint> // Include standard library for uint8_t
#include <cstddef> // Include standard library for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Define all possible values for icalproperty_transp
    icalproperty_transp transp_values[] = {
        ICAL_TRANSP_OPAQUE,
        ICAL_TRANSP_OPAQUENOCONFLICT, // Corrected the identifier
        ICAL_TRANSP_TRANSPARENT,
        ICAL_TRANSP_NONE
    };

    // Calculate the number of possible values
    size_t num_values = sizeof(transp_values) / sizeof(transp_values[0]);

    // Iterate over all possible values
    for (size_t i = 0; i < num_values; ++i) {
        icalproperty_transp transp_value = transp_values[i];

        // Call the function-under-test
        icalproperty *prop = icalproperty_new_transp(transp_value);

        // Clean up
        if (prop != NULL) {
            icalproperty_free(prop);
        }
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

    LLVMFuzzerTestOneInput_20(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
