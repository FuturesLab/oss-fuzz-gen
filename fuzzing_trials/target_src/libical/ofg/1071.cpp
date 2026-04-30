#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include <libical/ical.h> // Assuming the correct path to the ical library headers
}

extern "C" int LLVMFuzzerTestOneInput_1071(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzidaliasof = (char *)malloc(size + 1);
    if (tzidaliasof == NULL) {
        return 0;
    }
    memcpy(tzidaliasof, data, size);
    tzidaliasof[size] = '\0';

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZIDALIASOF_PROPERTY);
    if (prop == NULL) {
        free(tzidaliasof);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_tzidaliasof(prop, tzidaliasof);

    // Clean up
    icalproperty_free(prop);
    free(tzidaliasof);

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

    LLVMFuzzerTestOneInput_1071(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
