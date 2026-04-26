#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1135(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to map to a valid icalrecurrencetype_skip value
    if (size < 1) {
        return 0;
    }

    // Map the first byte of data to an icalrecurrencetype_skip value
    icalrecurrencetype_skip skip_option = static_cast<icalrecurrencetype_skip>(data[0] % 4);

    // Call the function-under-test
    const char *result = icalrecur_skip_to_string(skip_option);

    // Use the result in some way to avoid compiler optimizations
    if (result != NULL) {
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

    LLVMFuzzerTestOneInput_1135(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
