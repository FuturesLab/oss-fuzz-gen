#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_843(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int max_result_size = 0;
    for (size_t i = 0; i < sizeof(int) && i < size; ++i) {
        max_result_size |= data[i] << (i * 8);
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_new_maxresultssize(max_result_size);

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

    LLVMFuzzerTestOneInput_843(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
