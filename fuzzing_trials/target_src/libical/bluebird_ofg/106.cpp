#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this to use strlen

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Check if the data is null-terminated to prevent buffer overflow
    if (size == 0 || data[size - 1] != '\0') {
        return 0; // Return early if data is not null-terminated
    }

    // Initialize a valid icalproperty object
    icalproperty *property = icalproperty_new_xlicmimecharset((const char *)data);

    // Check if property was created successfully
    if (!property) {
        return 0; // Return early if property creation failed
    }

    // Call the function-under-test
    const char *charset = icalproperty_get_xlicmimecharset(property);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_106(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
