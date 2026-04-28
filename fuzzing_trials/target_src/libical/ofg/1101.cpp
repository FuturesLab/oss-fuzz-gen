#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1101(const uint8_t *data, size_t size) {
    // Ensure there is enough data for a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *patch_version = new char[size + 1];
    memcpy(patch_version, data, size);
    patch_version[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_patchversion(patch_version, nullptr);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }

    delete[] patch_version;

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

    LLVMFuzzerTestOneInput_1101(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
