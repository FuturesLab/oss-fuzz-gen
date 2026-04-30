extern "C" {
    #include <libical/ical.h>
    #include <stdlib.h>
    #include <string.h>
}

#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_818(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for safe conversion to a C-string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // If memory allocation fails, exit early
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_recurlimit(input);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    free(input);

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

    LLVMFuzzerTestOneInput_818(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
