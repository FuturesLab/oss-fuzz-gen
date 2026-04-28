#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libical/ical.h>

extern "C" {
    bool icalcomponent_isa_component(const void *);
}

extern "C" int LLVMFuzzerTestOneInput_957(const uint8_t *data, size_t size) {
    if (size < sizeof(void *)) {
        return 0;
    }

    // Use the input data as a pointer after casting
    const void *inputPtr = reinterpret_cast<const void *>(data);

    // Call the function-under-test
    bool result = icalcomponent_isa_component(inputPtr);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        volatile int dummy = 0;
        dummy++;
    }

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

    LLVMFuzzerTestOneInput_957(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
