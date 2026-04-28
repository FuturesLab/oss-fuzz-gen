#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use it as a C-string.
    char *cstr = static_cast<char*>(malloc(size + 1));
    if (cstr == nullptr) {
        return 0; // Fail gracefully if memory allocation fails.
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0'; // Null-terminate the string.

    // Call the function-under-test with the fuzzed input.
    icalproperty *prop = icalproperty_new_x(cstr);

    // Clean up allocated memory.
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    free(cstr);

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

    LLVMFuzzerTestOneInput_98(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
