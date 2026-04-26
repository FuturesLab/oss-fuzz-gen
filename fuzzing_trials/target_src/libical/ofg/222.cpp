#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int tzoffsetfrom = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        tzoffsetfrom |= data[i] << (i * 8);
    }

    // Call the function-under-test
    icalproperty* prop = icalproperty_new_tzoffsetfrom(tzoffsetfrom);

    // Clean up if the property was created
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

    LLVMFuzzerTestOneInput_222(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
