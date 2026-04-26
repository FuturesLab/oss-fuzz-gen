#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with for both icalproperty and icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalproperty
    icalproperty *property = icalproperty_new(ICAL_TZUNTIL_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract an icaltimetype from the data
    struct icaltimetype tt;
    memcpy(&tt, data, sizeof(struct icaltimetype));

    // Ensure the icaltimetype is valid
    tt.is_date = 1; // Set is_date to a non-zero value to ensure it's not NULL

    // Call the function under test
    icalproperty_set_tzuntil(property, tt);

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

    LLVMFuzzerTestOneInput_88(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
