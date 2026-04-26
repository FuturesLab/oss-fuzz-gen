#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_231(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to prevent buffer overflow
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *prop = icalproperty_new_from_string((const char *)data);
    
    // Ensure the property is not NULL
    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *voter = icalproperty_get_voter(prop);

    // Use the result in some way to prevent compiler optimizations
    if (voter != NULL) {
        // For example, just print the first character
        volatile char first_char = voter[0];
    }

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_231(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
