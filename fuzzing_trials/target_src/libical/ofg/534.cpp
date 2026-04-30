#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_534(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an int value
    if (size < sizeof(int)) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_REPEAT_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Extract an int value from the input data
    int repeat_value = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        repeat_value |= data[i] << (i * 8);
    }

    // Call the function-under-test
    icalproperty_set_repeat(prop, repeat_value);

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

    LLVMFuzzerTestOneInput_534(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
