#include <stdint.h>
#include <stddef.h>

// Wrap libical includes with extern "C" since libical is a C library
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1020(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a status value
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Extract a status value from the data
    // Use the correct enum type from libical
    icalproperty_status status = static_cast<icalproperty_status>(data[0] % 4);

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

    LLVMFuzzerTestOneInput_1020(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
