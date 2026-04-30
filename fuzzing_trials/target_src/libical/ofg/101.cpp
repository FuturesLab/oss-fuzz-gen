#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *str = (char *)malloc(size + 1);
    if (!str) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(str, data, size);
    str[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(str);

    // Ensure that the property is not NULL before proceeding
    if (prop != NULL) {
        // Call the function-under-test
        struct icaltimetype lastModified = icalproperty_get_lastmodified(prop);

        // Clean up the icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated string
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

    LLVMFuzzerTestOneInput_101(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
