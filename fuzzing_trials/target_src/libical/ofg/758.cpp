#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_758(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an int value
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a new icalproperty object
    icalproperty *property = icalproperty_new(ICAL_TZOFFSETFROM_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract an int value from the data
    int offset = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    icalproperty_set_tzoffsetfrom(property, offset);

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

    LLVMFuzzerTestOneInput_758(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
