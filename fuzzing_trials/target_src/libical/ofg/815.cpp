#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_815(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-style string
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    icalproperty_action action = icalproperty_string_to_action(inputString);

    // Clean up
    delete[] inputString;

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

    LLVMFuzzerTestOneInput_815(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
