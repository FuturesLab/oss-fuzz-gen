#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_572(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an icalproperty_kind value
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Extract an icalproperty_kind value from the input data
    icalproperty_kind prop_kind = static_cast<icalproperty_kind>(*data);

    // Call the function-under-test
    icalvalue_kind value_kind = icalproperty_kind_to_value_kind(prop_kind);

    // Use the result in some way to avoid any compiler optimizations
    if (value_kind == ICAL_VALUE_NONE) {
        // Do something trivial
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

    LLVMFuzzerTestOneInput_572(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
