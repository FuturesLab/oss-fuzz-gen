#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_821(const uint8_t *data, size_t size) {
    // Ensure that size is non-zero and data is not NULL
    if (size == 0 || data == nullptr) {
        return 0;
    }

    // Copy the data to a null-terminated string
    char *target_string = (char *)malloc(size + 1);
    if (target_string == nullptr) {
        return 0;
    }
    memcpy(target_string, data, size);
    target_string[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_from_string(target_string);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    free(target_string);

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

    LLVMFuzzerTestOneInput_821(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
