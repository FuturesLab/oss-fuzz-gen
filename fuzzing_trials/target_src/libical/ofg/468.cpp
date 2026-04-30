#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_468(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a 32-bit integer
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an icalcomponent_kind
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(*(reinterpret_cast<const uint32_t*>(data)));

    // Call the function-under-test
    const char *result = icalcomponent_kind_to_string(kind);

    // Optionally, do something with the result to avoid compiler optimizations
    if (result) {
        // For example, just access the first character
        volatile char firstChar = result[0];
        (void)firstChar; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_468(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
