#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_595(const uint8_t *data, size_t size) {
    // Ensure the size of data is sufficient for our needs
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int integer_input = 0;
    for (size_t i = 0; i < sizeof(int) && i < size; ++i) {
        integer_input = (integer_input << 8) | data[i];
    }

    // Create a dummy void pointer
    void *dummy_void_ptr = static_cast<void*>(const_cast<uint8_t*>(data));

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_expand(integer_input, dummy_void_ptr);

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

    LLVMFuzzerTestOneInput_595(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
