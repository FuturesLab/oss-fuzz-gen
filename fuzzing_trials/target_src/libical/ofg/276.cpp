#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h> // Adjust the path to the correct location of ical.h
}

extern "C" int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Interpret the first 4 bytes of data as an integer
    int enum_value = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    const char *result = icalproperty_enum_to_string(enum_value);

    // Optionally, you can do something with the result, like logging
    // But for fuzzing purposes, calling the function is sufficient

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

    LLVMFuzzerTestOneInput_276(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
