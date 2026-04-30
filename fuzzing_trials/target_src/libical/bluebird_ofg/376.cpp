#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_376(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to extract an icalproperty_transp value
    if (size < sizeof(icalproperty_transp)) {
        return 0;
    }

    // Cast the input data to an icalproperty_transp type
    icalproperty_transp transp_value = *(reinterpret_cast<const icalproperty_transp*>(data));

    // Call the function-under-test
    const char *result = icalproperty_transp_to_string(transp_value);

    // Use the result to prevent any compiler optimizations that might skip the function call
    if (result != nullptr) {
        volatile char dummy = result[0];
        (void)dummy;
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

    LLVMFuzzerTestOneInput_376(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
