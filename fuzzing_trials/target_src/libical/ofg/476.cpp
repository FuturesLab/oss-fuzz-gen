#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_476(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to create a new icalproperty with a repeat value
    int repeat_value = data[0];
    icalproperty *prop = icalproperty_new_repeat(repeat_value);

    // Call the function-under-test
    int repeat = icalproperty_get_repeat(prop);

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

    LLVMFuzzerTestOneInput_476(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
