#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_301(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a valid enum value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data to use as the enumeration value
    int enum_value = *((int*)data);
    icalproperty_method method = static_cast<icalproperty_method>(enum_value);

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_method(method, NULL);

    // Clean up if necessary
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_301(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
