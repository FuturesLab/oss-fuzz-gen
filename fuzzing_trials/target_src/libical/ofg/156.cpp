extern "C" {
#include <libical/ical.h>
}

#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string for the patch target
    char *patchtarget = new char[size + 1];
    memcpy(patchtarget, data, size);
    patchtarget[size] = '\0';

    // Create a new icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Call the function-under-test
    icalproperty_set_patchtarget(prop, patchtarget);

    // Clean up
    icalproperty_free(prop);
    delete[] patchtarget;

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

    LLVMFuzzerTestOneInput_156(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
