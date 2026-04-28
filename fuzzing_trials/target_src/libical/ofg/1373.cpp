#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// Assuming the icallimits_kind is an enum or similar type
typedef enum {
    ICALLIMITS_KIND_1,
    ICALLIMITS_KIND_2,
    ICALLIMITS_KIND_3,
    ICALLIMITS_KIND_MAX // Assuming there are multiple kinds
} icallimits_kind;

extern "C" {
    // Function-under-test
    size_t icallimit_get(icallimits_kind kind);
}

extern "C" int LLVMFuzzerTestOneInput_1373(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the icallimits_kind
    icallimits_kind kind = static_cast<icallimits_kind>(data[0] % ICALLIMITS_KIND_MAX);

    // Call the function-under-test
    size_t result = icallimit_get(kind);

    // Optionally print the result for debugging purposes
    printf("icallimit_get(%d) = %zu\n", kind, result);

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

    LLVMFuzzerTestOneInput_1373(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
