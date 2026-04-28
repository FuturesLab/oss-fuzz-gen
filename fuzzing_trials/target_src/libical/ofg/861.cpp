#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_861(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (!ical_string) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(ical_string);

    // Check if the property was successfully created
    if (prop != NULL) {
        // Call the function-under-test
        struct icaltimetype result = icalproperty_get_tzuntil(prop);

        // Clean up
        icalproperty_free(prop);
    }

    free(ical_string);

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

    LLVMFuzzerTestOneInput_861(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
