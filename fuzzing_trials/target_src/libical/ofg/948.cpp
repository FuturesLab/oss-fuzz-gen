#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_948(const uint8_t *data, size_t size) {
    // Ensure there is enough data to construct a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Extract icaltimetype from the input data
    struct icaltimetype maxdate;
    memcpy(&maxdate, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty_set_maxdate(prop, maxdate);

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

    LLVMFuzzerTestOneInput_948(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
