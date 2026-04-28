#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the missing header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the icalproperty and icaltimetype structures
    icalproperty *prop = icalproperty_new(ICAL_EXDATE_PROPERTY);
    struct icaltimetype exdate;

    // Copy data into the icaltimetype structure
    memcpy(&exdate, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty_set_exdate(prop, exdate);

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

    LLVMFuzzerTestOneInput_14(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
