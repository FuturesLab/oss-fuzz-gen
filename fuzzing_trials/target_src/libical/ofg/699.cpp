#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_699(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *xlicmimecid = (char *)malloc(size + 1);
    if (xlicmimecid == nullptr) {
        return 0; // If allocation fails, exit
    }

    // Copy data to the string and null-terminate it
    memcpy(xlicmimecid, data, size);
    xlicmimecid[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_xlicmimecid(xlicmimecid);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    free(xlicmimecid);

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

    LLVMFuzzerTestOneInput_699(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
