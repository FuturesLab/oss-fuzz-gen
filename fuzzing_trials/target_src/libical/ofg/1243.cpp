#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1243(const uint8_t *data, size_t size) {
    // Ensure the data is not empty to maximize coverage
    if (size == 0) {
        return 0;
    }

    // Initialize the icalproperty object with a specific property type
    icalproperty *prop = icalproperty_new(ICAL_OWNER_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    char *owner = (char *)malloc(size + 1);
    if (owner == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(owner, data, size);
    owner[size] = '\0';

    // Call the function-under-test
    icalproperty_set_owner(prop, owner);

    // Clean up
    free(owner);
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

    LLVMFuzzerTestOneInput_1243(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
