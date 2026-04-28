#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" {
    // Assuming the function is defined in a C library
    bool icalproperty_isa_property(void *);
}

extern "C" int LLVMFuzzerTestOneInput_610(const uint8_t *data, size_t size) {
    // Ensure that there is enough data to use as a pointer
    if (size < sizeof(void *)) {
        return 0;
    }

    // Cast the data to a pointer type
    void *ptr = (void *)data;

    // Call the function-under-test
    bool result = icalproperty_isa_property(ptr);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

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

    LLVMFuzzerTestOneInput_610(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
