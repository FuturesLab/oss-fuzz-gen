#include <stdint.h>
#include <stddef.h>

// Wrap all C headers and functions in extern "C" to ensure proper linkage
extern "C" {
    #include <libical/ical.h>

    // Declare the function-under-test
    void icalproperty_set_status(icalproperty *, icalproperty_status);
}

extern "C" int LLVMFuzzerTestOneInput_1019(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract a status value
    if (size < sizeof(icalproperty_status)) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_STATUS_PROPERTY);

    // Extract a status value from the input data
    icalproperty_status status = static_cast<icalproperty_status>(data[0]);

    // Call the function-under-test
    icalproperty_set_status(prop, status);

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

    LLVMFuzzerTestOneInput_1019(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
