#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Declare the function-under-test since the header is not available
    int icalrecurrencetype_month_month(short month_value);
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_500(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a short value
    if (size < sizeof(short)) {
        return 0;
    }

    // Extract a short value from the input data
    short month_value;
    month_value = *(reinterpret_cast<const short*>(data));

    // Call the function-under-test
    int result = icalrecurrencetype_month_month(month_value);

    // Return 0 to indicate the fuzzer should continue
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

    LLVMFuzzerTestOneInput_500(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
