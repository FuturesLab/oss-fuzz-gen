#include <cstdint>  // For uint8_t
#include <cstdlib>  // For malloc and free
#include <cstring>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1213(const uint8_t *data, size_t size) {
    // Ensure size is enough to create a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the data
    char *str = (char *)malloc(size + 1);
    if (!str) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0';

    // Ensure the string is a valid input for icalproperty_vanew_xlicclustercount
    // For this particular function, we need a valid integer string
    // Attempt to convert the string to an integer
    char *endptr;
    long value = strtol(str, &endptr, 10);

    // If the entire string was not a valid number, free and return
    if (*endptr != '\0') {
        free(str);
        return 0;
    }

    // Create a dummy non-null pointer for the second argument
    void *dummy_pointer = (void *)0x1; // Non-null dummy pointer

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_xlicclustercount(str, dummy_pointer, nullptr);

    // Clean up
    if (prop) {
        icalproperty_free(prop);
    }
    free(str);

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

    LLVMFuzzerTestOneInput_1213(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
