#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely convert to a C-style string.
    char *cstr = new char[size + 1];
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test with the C-style string.
    icalproperty_method result = icalproperty_string_to_method(cstr);

    // Clean up allocated memory.
    delete[] cstr;

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

    LLVMFuzzerTestOneInput_309(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
