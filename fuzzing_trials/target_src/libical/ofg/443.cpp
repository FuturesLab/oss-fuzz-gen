#include <cstddef>
#include <cstdint>

// Assuming icallimits_kind is an enum or a similar type
extern "C" {
    typedef enum {
        ICALLIMITS_KIND_A,
        ICALLIMITS_KIND_B,
        ICALLIMITS_KIND_C,
        ICALLIMITS_KIND_MAX
    } icallimits_kind;

    void icallimit_set(icallimits_kind kind, size_t limit);
}

extern "C" int LLVMFuzzerTestOneInput_443(const uint8_t *data, size_t size) {
    // Ensure we have enough data to select a kind and a limit
    if (size < sizeof(icallimits_kind) + sizeof(size_t)) {
        return 0;
    }

    // Extract icallimits_kind from the data
    icallimits_kind kind = static_cast<icallimits_kind>(data[0] % ICALLIMITS_KIND_MAX);

    // Extract size_t limit from the data
    size_t limit = 0;
    if (size >= sizeof(size_t)) {
        limit = *reinterpret_cast<const size_t*>(data + 1);
    }

    // Call the function under test
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

    LLVMFuzzerTestOneInput_443(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
