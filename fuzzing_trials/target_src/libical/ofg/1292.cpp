#include <stdint.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1292(const uint8_t *data, size_t size) {
    // Ensure that the data is large enough to be used as an icalproperty_kind
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Extract an icalproperty_kind from the input data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Call the function-under-test
    icalproperty *property = icalproperty_new(kind);

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

    LLVMFuzzerTestOneInput_1292(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
