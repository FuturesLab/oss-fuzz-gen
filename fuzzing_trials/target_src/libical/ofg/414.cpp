#include <cstdint>
#include <cstdlib>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_414(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to derive a valid icalproperty_resourcetype.
    if (size < sizeof(int)) {
        return 0;
    }

    // Convert the input data to an integer value.
    int input_value = 0;
    for (size_t i = 0; i < sizeof(int) && i < size; ++i) {
        input_value |= data[i] << (i * 8);
    }

    // Cast the integer value to icalproperty_resourcetype.
    icalproperty_resourcetype resourcetype = static_cast<icalproperty_resourcetype>(input_value);

    // Call the function-under-test.
    const char *result = icalproperty_resourcetype_to_string(resourcetype);

    // Use the result in some way to avoid compiler optimizations removing the call.
    if (result != nullptr) {
        // For fuzzing purposes, we don't need to do anything specific with the result.
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

    LLVMFuzzerTestOneInput_414(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
