#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_789(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *source = (char *)malloc(size + 1);
    if (source == NULL) {
        return 0;
    }

    // Copy the data into the source and null-terminate it
    memcpy(source, data, size);
    source[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_source(source);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    free(source);

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

    LLVMFuzzerTestOneInput_789(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
