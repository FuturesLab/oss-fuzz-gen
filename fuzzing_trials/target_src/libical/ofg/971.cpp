#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_971(const uint8_t *data, size_t size) {
    // Initialize a non-NULL icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Ensure the size is sufficient to read an integer
    if (size < sizeof(int)) {
        icalproperty_free(property);
        return 0;
    }

    // Extract an integer from the input data
    int sequence = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    icalproperty_set_sequence(property, sequence);

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

    LLVMFuzzerTestOneInput_971(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
