#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t

extern "C" {
    #include <libical/ical.h>
}

// The function-under-test: icalproperty_get_allow_empty_properties
extern "C" bool icalproperty_get_allow_empty_properties();

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Since the function icalproperty_get_allow_empty_properties does not take any parameters,
    // we can directly call it without needing to use the input data.
    bool result = icalproperty_get_allow_empty_properties();

    // The result can be used for further logic if needed, but for fuzzing purposes,
    // we just need to ensure the function is called.
    (void)result; // Suppress unused variable warning

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

    LLVMFuzzerTestOneInput_26(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
