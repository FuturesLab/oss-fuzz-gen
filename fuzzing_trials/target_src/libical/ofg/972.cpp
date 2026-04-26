#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_972(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for string operations
    char *stringData = new char[size + 1];
    memcpy(stringData, data, size);
    stringData[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_patchdelete(stringData, nullptr);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    delete[] stringData;

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

    LLVMFuzzerTestOneInput_972(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
