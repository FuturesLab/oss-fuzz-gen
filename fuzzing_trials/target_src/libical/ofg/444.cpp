#include <cstdint>
#include <cstddef>

// Assuming the icallimits_kind is an enum or similar type, define it here
typedef enum {
    ICALLIMIT_KIND_A,
    ICALLIMIT_KIND_B,
    ICALLIMIT_KIND_C,
    ICALLIMIT_KIND_MAX
} icallimits_kind;

// Forward declaration of the function-under-test
extern "C" void icallimit_set(icallimits_kind kind, size_t limit);

extern "C" int LLVMFuzzerTestOneInput_444(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract meaningful data
    if (size < 2) {
        return 0;
    }

    // Extract the icallimits_kind from the first byte of data
    icallimits_kind kind = static_cast<icallimits_kind>(data[0] % ICALLIMIT_KIND_MAX);

    // Extract the size_t limit from the remaining bytes
    size_t limit = static_cast<size_t>(data[1]);

    // Call the function-under-test
    icallimit_set(kind, limit);

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

    LLVMFuzzerTestOneInput_444(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
