#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // Include for size_t

// Assuming the function is defined in a C library, we use extern "C"
extern "C" {
    bool icalrecurrencetype_month_is_leap(short month);
}

extern "C" int LLVMFuzzerTestOneInput_520(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a short value
    if (size < sizeof(short)) {
        return 0;
    }

    // Extract a short value from the input data
    short month = *(reinterpret_cast<const short*>(data));

    // Call the function-under-test
    bool result = icalrecurrencetype_month_is_leap(month);

    // Use the result in some way to avoid compiler optimizations
    volatile bool use_result = result;
    (void)use_result;

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

    LLVMFuzzerTestOneInput_520(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
