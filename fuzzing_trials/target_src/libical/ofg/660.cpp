#include <cstdint>  // For uint8_t
#include <cstdlib>  // For malloc, free
#include <cstring>  // For memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_660(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a null-terminated string
    if (size < 1) {
        return 0;
    }
    
    // Create a null-terminated string for the name parameter
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Create an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_NO_PROPERTY);
    if (property == NULL) {
        free(name);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_name(property, name);

    // Clean up
    icalproperty_free(property);
    free(name);

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

    LLVMFuzzerTestOneInput_660(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
